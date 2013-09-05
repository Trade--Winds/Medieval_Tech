//
// Yields_Colonization_2071.cpp
// Written by Nightinggale
//
#include "CvGameCoreDLL.h"
#include "CvGlobals.h"
#include "YieldsTestBase.h"

#ifdef COLONIZATION_2071

// AI sells unconditionally to natives and Europe unless they are raw materials as well
void Check_YieldGroup_AI_Sell::build()
{
	YieldVector.push_back(YIELD_TRADE_GOODS);
}

// AI sells these in Europe
// AI can also sell unneeded raw materials even if they aren't listed here
void Check_YieldGroup_AI_Sell_To_Europe::build()
{
	YieldVector.push_back(YIELD_ORE);
}

// AI attemps to buy from natives as needed (or whenever offered?)
void Check_YieldGroup_AI_Buy_From_Natives::build()
{
	YieldVector.push_back(YIELD_TOOLS);
}

// AI attemps to buy from Europe (Europe as in vanilla functionality)
void Check_YieldGroup_AI_Buy_From_Europe::build()
{
	YieldVector.push_back(YIELD_TOOLS);
	YieldVector.push_back(YIELD_WEAPONS);
	YieldVector.push_back(YIELD_HORSES);
	YieldVector.push_back(YIELD_TRADE_GOODS);
}

// AI sells unless they are needed
// Used for production building input like ore, cotton etc.
void Check_YieldGroup_AI_Raw_Material::build()
{
	YieldVector.push_back(YIELD_ORE);
	YieldVector.push_back(YIELD_STONE);
}

// Yields to show up on city billboards
void Check_YieldGroup_City_Billboard::build()
{
	YieldVector.push_back(YIELD_HORSES);
	YieldVector.push_back(YIELD_TOOLS);
}

// yields, which are affected by an off by one offset error when displaying billboard icons
// TODO: find the real culprint of this bug instead of working around it.
void Check_YieldGroup_City_Billboard_Offset_Fix::build()
{
	YieldVector.push_back(YIELD_HORSES);
	YieldVector.push_back(YIELD_TOOLS);
}

// yield is either light or heavy armor (not both)
void Check_YieldGroup_Armor::build()
{
}

// yield is light armor
void Check_YieldGroup_Light_Armor::build()
{
}

// yield is heavy armor
void Check_YieldGroup_Heavy_Armor::build()
{
}

// check YieldTypes vs XML yield names
void BaseCheckYieldGroup::checkXML()
{
	// first argument is YieldTypes enum value while the second is the name in XML
	checkSingleXMLType(YIELD_FOOD,               "YIELD_FOOD");
	//checkSingleXMLType(YIELD_GRAIN,              "YIELD_GRAIN");
	checkSingleXMLType(YIELD_CATTLE,             "YIELD_CATTLE");
	checkSingleXMLType(YIELD_SHEEP,              "YIELD_SHEEP");
	checkSingleXMLType(YIELD_WOOL,               "YIELD_WOOL");
	checkSingleXMLType(YIELD_LUMBER,             "YIELD_LUMBER");
	checkSingleXMLType(YIELD_STONE,              "YIELD_STONE");
	checkSingleXMLType(YIELD_SILVER,             "YIELD_SILVER");
	checkSingleXMLType(YIELD_SALT,               "YIELD_SALT");
	checkSingleXMLType(YIELD_SPICES,             "YIELD_SPICES");
	checkSingleXMLType(YIELD_FUR,                "YIELD_FUR");
	checkSingleXMLType(YIELD_COTTON,             "YIELD_COTTON");
	checkSingleXMLType(YIELD_BARLEY,             "YIELD_BARLEY");
	checkSingleXMLType(YIELD_GRAPES,             "YIELD_GRAPES");
	checkSingleXMLType(YIELD_ORE,                "YIELD_ORE");
	checkSingleXMLType(YIELD_CLOTH,              "YIELD_CLOTH");
	checkSingleXMLType(YIELD_COATS,              "YIELD_COATS");
	checkSingleXMLType(YIELD_ALE,                "YIELD_ALE");
	checkSingleXMLType(YIELD_WINE,               "YIELD_WINE");
	checkSingleXMLType(YIELD_TOOLS,              "YIELD_TOOLS");
	checkSingleXMLType(YIELD_WEAPONS,            "YIELD_WEAPONS");
	checkSingleXMLType(YIELD_HORSES,             "YIELD_HORSES");
	checkSingleXMLType(YIELD_LEATHER_ARMOR,      "YIELD_LEATHER_ARMOR");
	checkSingleXMLType(YIELD_SCALE_ARMOR,        "YIELD_SCALE_ARMOR");
	checkSingleXMLType(YIELD_MAIL_ARMOR,         "YIELD_MAIL_ARMOR");
	checkSingleXMLType(YIELD_PLATE_ARMOR,        "YIELD_PLATE_ARMOR");
	checkSingleXMLType(YIELD_TRADE_GOODS,        "YIELD_TRADE_GOODS");
	checkSingleXMLType(YIELD_HAMMERS,            "YIELD_HAMMERS");
	checkSingleXMLType(YIELD_BELLS,              "YIELD_BELLS");
	checkSingleXMLType(YIELD_CROSSES,            "YIELD_CROSSES");
	checkSingleXMLType(YIELD_EDUCATION,          "YIELD_EDUCATION");
	checkSingleXMLType(YIELD_IDEAS,              "YIELD_IDEAS");
	checkSingleXMLType(YIELD_CULTURE,            "YIELD_CULTURE");
	checkSingleXMLType(YIELD_GOLD,               "YIELD_GOLD");

}
#endif // COLONIZATION_2071