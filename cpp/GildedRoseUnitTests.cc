#include <gtest/gtest.h>

#include "GildedRose.h"

using ::std::string;


bool operator==(Item const& lh, Item const& rh) {
    return lh.name == rh.name &&
           lh.sellIn == rh.sellIn &&
           lh.quality == rh.quality;
}

std::ostream& operator<< (::std::ostream& stream, Item const& item) {
    stream << "[" << item.name << ", sellin: " << item.sellIn << ", quality: " << item.quality << "]";
    return stream;
}

static const char *const BACKSTAGE_PASS = "Backstage passes to a TAFKAL80ETC concert";
static const char *const REGULAR = "Foo";
static const char *const BRIE = "Aged Brie";
static const char *const SULFURAS = "Sulfuras, Hand of Ragnaros";

TEST(UpdateRegularItem, givenSellInIsPositive_shouldDecreaseSellInBy1AndQualityBy1) {
    // given
    auto item = Item(REGULAR, 5, 3);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(REGULAR, 4, 2));
}

TEST(UpdateRegularItem, givenSellInIs0_shouldDecreaseSellInBy1AndQualityBy2) {
    // given
    auto item = Item(REGULAR, 0, 3);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(REGULAR, -1, 1));
}

TEST(UpdateRegularItem, givenSellInIsNegative_shouldDecreaseSellInBy1AndQualityBy2) {
    // given
    auto item = Item(REGULAR, -5, 3);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(REGULAR, -6, 1));
}


TEST(UpdateRegularItem, givenQualityIs0_shouldNotDecreaseQuality) {
    // given
    auto item = Item(REGULAR, 5, 0);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(REGULAR, 4, 0));
}

TEST(UpdateAgedBrie, givenSellInIsPositive_shouldDecreaseSellInBy1AndIncreaseQualityBy1) {
    // given
    auto item = Item(BRIE, 5, 3);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(BRIE, 4, 4));
}


TEST(UpdateAgedBrie, givenSellInIs0_shouldDecreaseSellInBy1AndIncreaseQualityBy2) {
    // given
    auto item = Item(BRIE, 0, 3);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(BRIE, -1, 5));
}

TEST(UpdateAgedBrie, givenSellInIsNegative_shouldDecreaseSellInBy1AndIncreaseQualityBy2) {
    // given
    auto item = Item(BRIE, -5, 3);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(BRIE, -6, 5));
}


TEST(UpdateAgedBrie, givenQualityIs50_shouldNotIncreaseQuality) {
    // given
    auto item = Item(BRIE, 5, 50);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(BRIE, 4, 50));
}

TEST(UpdateAgedBrie, givenQualityIs49AndSellInIs0_shouldCapQualityTo50) {
    // given
    auto item = Item(BRIE, 0, 49);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(BRIE, -1, 50));
}

TEST(UpdateSulfuras, givenSellInIsPositive_shouldNotChange) {
    // given
    auto item = Item(SULFURAS, 6, 80);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(SULFURAS, 6, 80));
}

TEST(UpdateSulfuras, givenSellInIs0_shouldNotChange) {
    // given
    auto item = Item(SULFURAS, 0, 80);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(SULFURAS, 0, 80));
}

TEST(UpdateBackstagePasses, givenSellInIs10_shouldIncreaseQualityBy2) {
    // given
    auto item = Item(BACKSTAGE_PASS, 10, 5);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(BACKSTAGE_PASS, 9, 7));
}

TEST(UpdateBackstagePasses, givenSellInIs6_shouldIncreaseQualityBy2) {
    // given
    auto item = Item(BACKSTAGE_PASS, 6, 5);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(BACKSTAGE_PASS, 5, 7));
}

TEST(UpdateBackstagePasses, givenSellInIs5_shouldIncreaseQualityBy3) {
    // given
    auto item = Item(BACKSTAGE_PASS, 5, 5);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(BACKSTAGE_PASS, 4, 8));
}

TEST(UpdateBackstagePasses, givenSellInIs0_shouldDropQualityTo0) {
    // given
    auto item = Item(BACKSTAGE_PASS, 0, 10);
    GildedRose app({item});

    // when
    app.updateQuality();

    // then
    EXPECT_EQ(app.items[0], Item(BACKSTAGE_PASS, -1, 0));
}

TEST(UpdateBackstagePasses, givenSellInIsNegative_shouldDropQualityTo0) {
    auto item = Item(BACKSTAGE_PASS, -1, 10);
    GildedRose app({item});

    app.updateQuality();

    EXPECT_EQ(app.items[0], Item(BACKSTAGE_PASS, -2, 0));
}

void example() {
    ::std::vector<Item> items;
    items.push_back(Item("+5 Dexterity Vest", 10, 20));
    items.push_back(Item(BRIE, 2, 0));
    items.push_back(Item("Elixir of the Mongoose", 5, 7));
    items.push_back(Item(SULFURAS, 0, 80));
    items.push_back(Item(BACKSTAGE_PASS, 15, 20));
    items.push_back(Item("Conjured Mana Cake", 3, 6));
    GildedRose app(items);
    app.updateQuality();
}
