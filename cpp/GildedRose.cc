#include "GildedRose.h"


GildedRose::GildedRose(::std::vector<Item> const& items) : items(items)
{}

GildedRose::GildedRose(::std::vector<Item> && items) : items(::std::move(items))
{}

void GildedRose::updateQuality()
{
const std::string aged_Brie = "Aged Brie";
const std::string backstage_Pass = "Backstage passes to a TAFKAL80ETC concert";
const std::string Sulfuras = "Sulfuras, Hand of Ragnaros";
   
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].name != aged_Brie && items[i].name != backstage_Pass items[i].name != Sulfuras && items[i].quality > 0)
        {    
            items[i].quality--;
        }
        else if (items[i].quality < 50)
        {
            items[i].quality++;

            if (items[i].name == backstage_Pass)
            {
                if (items[i].sellIn < 11)
                {       
                    items[i].quality++;
                }
                if (items[i].sellIn < 6 && items[i].quality < 50)
                {
                    items[i].quality++;
                }
            }
        }
        

        if (items[i].name != Sulfuras)
        {
            items[i].sellIn--;
        }

        if (items[i].sellIn < 0)
        {
            if (items[i].name != aged_Brie && items[i].name != backstage_Pass)
            {
                 if (items[i].quality > 0 && items[i].name != Sulfuras)
                {
                    items[i].quality--;
                } 
                else
                {
                    items[i].quality = 0;
                }
            }
            else
            {
                if (items[i].quality < 50)
                {
                    items[i].quality++;
                }
            }
        }
    }
}

