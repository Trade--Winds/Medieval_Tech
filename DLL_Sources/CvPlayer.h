#pragma once

// player.h

#ifndef CIV4_PLAYER_H
#define CIV4_PLAYER_H

#include "CvCityAI.h"
#include "CvSelectionGroupAI.h"
#include "LinkedList.h"
#include "CvIdVector.h"
#include "CvTalkingHeadMessage.h"

/// PlotGroup - start - Nightinggale
#include "CvPlotGroup.h"
/// PlotGroup - end - Nightinggale

class CvDiploParameters;
class CvPopupInfo;
class CvEventTriggerInfo;
class CvTradeRoute;
class CvUnitAI;

typedef std::list<CvTalkingHeadMessage> CvMessageQueue;
typedef std::list<CvPopupInfo*> CvPopupQueue;
typedef std::list<CvDiploParameters*> CvDiploQueue;
typedef stdext::hash_map<int, int> CvTurnScoreMap;
typedef stdext::hash_map<EventTypes, EventTriggeredData> CvEventMap;
typedef std::vector< std::pair<UnitCombatTypes, PromotionTypes> > UnitCombatPromotionArray;
typedef std::vector< std::pair<UnitClassTypes, PromotionTypes> > UnitClassPromotionArray;
typedef std::vector< std::pair<CivilizationTypes, LeaderHeadTypes> > CivLeaderArray;

class CvPlayer
{
public:
	CvPlayer();
	virtual ~CvPlayer();

	DllExport void init(PlayerTypes eID);
	DllExport void setupGraphical();
	DllExport void reset(PlayerTypes eID = NO_PLAYER, bool bConstructorCall = false);

protected:

	void uninit();

public:

	void initFreeState();
	void initFreeUnits();
	void initImmigration();
	void addFreeUnitAI(UnitAITypes eUnitAI, int iCount);
	CvUnit* addFreeUnit(UnitTypes eUnit, ProfessionTypes eProfession, UnitAITypes eUnitAI = NO_UNITAI);
	int startingPlotRange() const;
	int startingPlotDistanceFactor(CvPlot* pPlot, PlayerTypes ePlayer, int iRange) const;
	int findStartingArea() const;
	CvPlot* findStartingPlot(bool bRandomize = false);
	///Tks Med
	DllExport CvCity* initCity(int iX, int iY, bool bBumpUnits, int iType = 0);
	///Tke
	void acquireCity(CvCity* pCity, bool bConquest, bool bTrade);
	void killCities();
	const CvWString getNewCityName() const;
	const CvWString& addNewCityName();
	void getCivilizationCityName(CvWString& szBuffer, CivilizationTypes eCivilization) const;
	bool isCityNameValid(const CvWString& szName, bool bTestDestroyed = true) const;
	DllExport CvUnit* initUnit(UnitTypes eUnit, ProfessionTypes eProfession, int iX, int iY, UnitAITypes eUnitAI = NO_UNITAI, DirectionTypes eFacingDirection = NO_DIRECTION, int iYieldStored = 0);
	DllExport CvUnit* initEuropeUnit(UnitTypes eUnit, UnitAITypes eUnitAI = NO_UNITAI, DirectionTypes eFacingDirection = NO_DIRECTION);
	void killUnits();
	DllExport CvSelectionGroup* cycleSelectionGroups(CvUnit* pUnit, bool bForward, bool* pbWrap);
	bool hasTrait(TraitTypes eTrait) const;
	int getTraitCount(TraitTypes eTrait) const;
	void changeTraitCount(TraitTypes eTrait, int iChange);
	int getMercantileFactor() const;
	DllExport bool isHuman() const;
	DllExport void updateHuman();
	bool isNative() const;
	bool isAlwaysOpenBorders() const;
	DllExport const wchar* getName(uint uiForm = 0) const;
	DllExport const wchar* getNameKey() const;
	DllExport const wchar* getCivilizationDescription(uint uiForm = 0) const;
	DllExport const wchar* getCivilizationDescriptionKey() const;
	DllExport const wchar* getCivilizationShortDescription(uint uiForm = 0) const;
	DllExport const wchar* getCivilizationShortDescriptionKey() const;
	DllExport const wchar* getCivilizationAdjective(uint uiForm = 0) const;
	DllExport const wchar* getCivilizationAdjectiveKey() const;
	DllExport const char* getFlagDecal() const;
	DllExport bool isWhiteFlag() const;
	DllExport bool isInvertFlag() const;
	DllExport const CvWString getWorstEnemyName() const;
	DllExport ArtStyleTypes getArtStyleType() const;
	DllExport const TCHAR* getUnitButton(UnitTypes eUnit) const;
	void doTurn();
	void doTurnUnits();
	void doEra();

	void verifyCivics();

	void updateYield();
	void updateCityPlotYield();
	void updateCitySight(bool bIncrement, bool bUpdatePlotGroups);

	void updateTimers();

	DllExport bool hasReadyUnit(bool bAny = false) const;
	DllExport bool hasAutoUnit() const;
	DllExport bool hasBusyUnit() const;
	int calculateScore(bool bFinal = false, bool bVictory = false) const;
	int getScoreTaxFactor() const;
	int findBestFoundValue() const;
	DllExport int upgradeAllPrice(UnitTypes eUpgradeUnit, UnitTypes eFromUnit);
	int countNumCoastalCities() const;
	int countNumCoastalCitiesByArea(CvArea* pArea) const;
	int countTotalCulture() const;
	int countTotalYieldStored(YieldTypes eYield) const;
	int countCityFeatures(FeatureTypes eFeature) const;
	int countNumBuildings(BuildingTypes eBuilding) const;
	DllExport bool canContact(PlayerTypes ePlayer) const;
	void contact(PlayerTypes ePlayer);
	DllExport void handleDiploEvent(DiploEventTypes eDiploEvent, PlayerTypes ePlayer, int iData1, int iData2);
	bool canTradeWith(PlayerTypes eWhoTo) const;
	bool canReceiveTradeCity(PlayerTypes eFromPlayer) const;
	DllExport bool canTradeItem(PlayerTypes eWhoTo, TradeData item, bool bTestDenial = false) const;
	DllExport DenialTypes getTradeDenial(PlayerTypes eWhoTo, TradeData item) const;
	bool isTradingWithTeam(TeamTypes eTeam, bool bIncludeCancelable) const;
	bool canStopTradingWithTeam(TeamTypes eTeam, bool bContinueNotTrading = false) const;
	void stopTradingWithTeam(TeamTypes eTeam);
	void killAllDeals();
	void findNewCapital();
	DllExport bool canRaze(CvCity* pCity) const;
	void raze(CvCity* pCity);
	void disband(CvCity* pCity);
	bool canReceiveGoody(CvPlot* pPlot, GoodyTypes eGoody, const CvUnit* pUnit) const;
	int receiveGoody(CvPlot* pPlot, GoodyTypes eGoody, CvUnit* pUnit);
	void receiveRandomGoody(CvPlot* pPlot, GoodyTypes eGoody, CvUnit* pUnit);
	void doGoody(CvPlot* pPlot, CvUnit* pUnit);
	///Tks Med
	DllExport bool canFound(int iX, int iY, bool bTestVisible = false, int iCityType = 0) const;
	void found(int iX, int iY, int iType = 0);
	///Tke
	DllExport bool canTrain(UnitTypes eUnit, bool bContinue = false, bool bTestVisible = false, bool bIgnoreCost = false) const;
	bool canConstruct(BuildingTypes eBuilding, bool bContinue = false, bool bTestVisible = false, bool bIgnoreCost = false) const;
	DllExport int getYieldProductionNeeded(UnitTypes eUnit, YieldTypes eYield) const;
	DllExport int getYieldProductionNeeded(BuildingTypes eBuilding, YieldTypes eYield) const;
	int getProductionModifier(UnitTypes eUnit) const;
	int getProductionModifier(BuildingTypes eBuilding) const;
	DllExport int getBuildingClassPrereqBuilding(BuildingTypes eBuilding, BuildingClassTypes ePrereqBuildingClass, int iExtra = 0) const;
	void removeBuildingClass(BuildingClassTypes eBuildingClass);
	void processTrait(TraitTypes eTrait, int iChange);
	void processFather(FatherTypes eFather, int iChange);
	void processFatherOnce(FatherTypes eFather);
	int getFatherPointMultiplier() const;
	void setFatherPointMultiplier(int iValue);
	void changeFatherPoints(FatherPointTypes ePointType, int iChange);
	int getBuildCost(const CvPlot* pPlot, BuildTypes eBuild) const;
	bool canBuild(const CvPlot* pPlot, BuildTypes eBuild, bool bTestEra = false, bool bTestVisible = false) const;
	RouteTypes getBestRoute(CvPlot* pPlot = NULL) const;
	int getImprovementUpgradeRate() const;
	int calculateTotalYield(YieldTypes eYield) const;
	void calculateTotalYields(int aiYields[]) const;
	bool isCivic(CivicTypes eCivic) const;
	bool canDoCivics(CivicTypes eCivic) const;
	DllExport int greatGeneralThreshold() const;
	int immigrationThreshold() const;
	int revolutionEuropeUnitThreshold() const;
	DllExport CvPlot* getStartingPlot() const;
	DllExport void setStartingPlot(CvPlot* pNewValue, bool bUpdateStartDist);
	DllExport int getTotalPopulation() const;
	int getAveragePopulation() const;
	void changeTotalPopulation(int iChange);
	long getRealPopulation() const;
	int getTotalLand() const;
	void changeTotalLand(int iChange);
	int getTotalLandScored() const;
	void changeTotalLandScored(int iChange);
	DllExport int getGold() const;
	DllExport void setGold(int iNewValue);
	DllExport void changeGold(int iChange);
	int getExtraTradeMultiplier(PlayerTypes eOtherPlayer) const;
	DllExport int getAdvancedStartPoints() const;
	DllExport void setAdvancedStartPoints(int iNewValue);
	DllExport void changeAdvancedStartPoints(int iChange);
	DllExport void doAdvancedStartAction(AdvancedStartActionTypes eAction, int iX, int iY, int iData, bool bAdd);
	DllExport int getAdvancedStartUnitCost(UnitTypes eUnit, bool bAdd, CvPlot* pPlot = NULL);
	DllExport int getAdvancedStartCityCost(bool bAdd, CvPlot* pPlot = NULL);
	DllExport int getAdvancedStartPopCost(bool bAdd, CvCity* pCity = NULL);
	DllExport int getAdvancedStartCultureCost(bool bAdd, CvCity* pCity = NULL);
	DllExport int getAdvancedStartBuildingCost(BuildingTypes eBuilding, bool bAdd, CvCity* pCity = NULL);
	DllExport int getAdvancedStartImprovementCost(ImprovementTypes eImprovement, bool bAdd, CvPlot* pPlot = NULL);
	DllExport int getAdvancedStartRouteCost(RouteTypes eRoute, bool bAdd, CvPlot* pPlot = NULL);
	DllExport int getAdvancedStartVisibilityCost(bool bAdd, CvPlot* pPlot = NULL);

	void createGreatGeneral(UnitTypes eGreatGeneralUnit, bool bIncrementExperience, int iX, int iY);
	int getGreatGeneralsCreated() const;
	void incrementGreatGeneralsCreated();
	int getGreatGeneralsThresholdModifier() const;
	void changeGreatGeneralsThresholdModifier(int iChange);
	int getGreatGeneralRateModifier() const;
	void changeGreatGeneralRateModifier(int iChange);
	int getDomesticGreatGeneralRateModifier() const;
	void changeDomesticGreatGeneralRateModifier(int iChange);
	int getImmigrationThresholdMultiplier() const;
	void setImmigrationThresholdMultiplier(int iChange);
	int getRevolutionEuropeUnitThresholdMultiplier() const;
	void setRevolutionEuropeUnitThresholdMultiplier(int iChange);
	int getKingNumUnitMultiplier() const;
	void setKingNumUnitMultiplier(int iChange);
	int getNativeAngerModifier() const;
	void changeNativeAngerModifier(int iChange);
	int getFreeExperience() const;
	void changeFreeExperience(int iChange);
	int getWorkerSpeedModifier() const;
	void changeWorkerSpeedModifier(int iChange);
	int getImprovementUpgradeRateModifier() const;
	void changeImprovementUpgradeRateModifier(int iChange);
	int getMilitaryProductionModifier() const;
	void changeMilitaryProductionModifier(int iChange);
	int getCityDefenseModifier() const;
	void changeCityDefenseModifier(int iChange);
	int getHighestUnitLevel() const;
	void setHighestUnitLevel(int iNewValue);
	DllExport int getFatherOverflowBells() const;
	void setFatherOverflowBells(int iNewValue);
	void changeFatherOverflowBells(int iChange);
	int getExpInBorderModifier() const;
	void changeExpInBorderModifier(int iChange);
	int getLevelExperienceModifier() const;
	void changeLevelExperienceModifier(int iChange);
	DllExport CvCity* getCapitalCity() const;
	void setCapitalCity(CvCity* pNewCapitalCity);
	DllExport CvCity* getPrimaryCity() const;
	int getCitiesLost() const;
	void changeCitiesLost(int iChange);
	DllExport int getAssets() const;
	void changeAssets(int iChange);
	DllExport int getPower() const;
	void changePower(int iChange);
	DllExport int getPopScore() const;
	void changePopScore(int iChange);
	DllExport int getLandScore() const;
	void changeLandScore(int iChange);
	DllExport int getFatherScore() const;
	void changeFatherScore(int iChange);
	int getCombatExperience() const;
	void setCombatExperience(int iExperience);
	void changeCombatExperience(int iChange);
	DllExport bool isConnected() const;
	DllExport int getNetID() const;
	DllExport void setNetID(int iNetID);
	DllExport void sendReminder();

	uint getStartTime() const;
	DllExport void setStartTime(uint uiStartTime);
	DllExport uint getTotalTimePlayed() const;
	DllExport bool isAlive() const;
	DllExport bool isEverAlive() const;
	void setAlive(bool bNewValue);
	void verifyAlive();
	DllExport bool isTurnActive() const;
	DllExport void setTurnActive(bool bNewValue, bool bDoTurn = true);

	bool isAutoMoves() const;
	DllExport void setAutoMoves(bool bNewValue);
	DllExport void setTurnActiveForPbem(bool bActive);

	DllExport bool isPbemNewTurn() const;
	DllExport void setPbemNewTurn(bool bNew);

	bool isEndTurn() const;
	DllExport void setEndTurn(bool bNewValue);

	DllExport bool isTurnDone() const;
	bool isExtendedGame() const;
	DllExport void makeExtendedGame();
	bool isFoundedFirstCity() const;
	void setFoundedFirstCity(bool bNewValue);
	DllExport PlayerTypes getID() const;
	DllExport HandicapTypes getHandicapType() const;
	DllExport CivilizationTypes getCivilizationType() const;
	DllExport LeaderHeadTypes getLeaderType() const;
	LeaderHeadTypes getPersonalityType() const;
	void setPersonalityType(LeaderHeadTypes eNewValue);
	DllExport EraTypes getCurrentEra() const;
	void setCurrentEra(EraTypes eNewValue);
	DllExport PlayerTypes getParent() const;
	DllExport void setParent(PlayerTypes eParent);
	DllExport TeamTypes getTeam() const;
	void setTeam(TeamTypes eTeam);
	void updateTeamType();
	YieldTypes getImmigrationConversion() const;
	void setImmigrationConversion(YieldTypes eConversion);
	DllExport PlayerColorTypes getPlayerColor() const;
	DllExport int getPlayerTextColorR() const;
	DllExport int getPlayerTextColorG() const;
	DllExport int getPlayerTextColorB() const;
	DllExport int getPlayerTextColorA() const;
	int getSeaPlotYield(YieldTypes eIndex) const;
	void changeSeaPlotYield(YieldTypes eIndex, int iChange);
	int getYieldRateModifier(YieldTypes eIndex) const;
	int getTaxYieldRateModifier(YieldTypes eIndex) const;
	void changeYieldRateModifier(YieldTypes eIndex, int iChange);
	int getCapitalYieldRateModifier(YieldTypes eIndex) const;
	void changeCapitalYieldRateModifier(YieldTypes eIndex, int iChange);
	int getBuildingRequiredYieldModifier(YieldTypes eIndex) const;
	void changeBuildingRequiredYieldModifier(YieldTypes eIndex, int iChange);
	int getCityExtraYield(YieldTypes eIndex) const;
	void updateCityExtraYield(YieldTypes eIndex);
	int getExtraYieldThreshold(YieldTypes eIndex) const;
	void updateExtraYieldThreshold(YieldTypes eIndex);
	int getYieldRate(YieldTypes eIndex) const;
	bool isYieldEuropeTradable(YieldTypes eIndex, EuropeTypes eTradeScreen=NO_EUROPE) const;
	void setYieldEuropeTradable(YieldTypes eIndex, bool bTradeable);
	void setYieldEuropeTradableAll();
	bool isFeatAccomplished(FeatTypes eIndex) const;
	void setFeatAccomplished(FeatTypes eIndex, bool bNewValue);
	DllExport bool shouldDisplayFeatPopup(FeatTypes eIndex) const;
	DllExport bool isOption(PlayerOptionTypes eIndex) const;
	DllExport void setOption(PlayerOptionTypes eIndex, bool bNewValue);
	DllExport bool isPlayable() const;
	DllExport void setPlayable(bool bNewValue);
	int getImprovementCount(ImprovementTypes eIndex) const;
	void changeImprovementCount(ImprovementTypes eIndex, int iChange);
	int getFreeBuildingCount(BuildingTypes eIndex) const;
	bool isBuildingFree(BuildingTypes eIndex) const;
	void changeFreeBuildingCount(BuildingTypes eIndex, int iChange);
	int getUnitClassCount(UnitClassTypes eIndex) const;
	void changeUnitClassCount(UnitClassTypes eIndex, int iChange);
	int getUnitClassMaking(UnitClassTypes eIndex) const;
	void changeUnitClassMaking(UnitClassTypes eIndex, int iChange);
	int getUnitClassImmigrated(UnitClassTypes eIndex) const;
	void changeUnitClassImmigrated(UnitClassTypes eIndex, int iChange);
	int getUnitClassCountPlusMaking(UnitClassTypes eIndex) const;
	int getUnitMoveChange(UnitClassTypes eIndex) const;
	DllExport void changeUnitMoveChange(UnitClassTypes eIndex, int iChange);
	int getUnitStrengthModifier(UnitClassTypes eIndex) const;
	DllExport void changeUnitStrengthModifier(UnitClassTypes eIndex, int iChange);
	int getProfessionCombatChange(ProfessionTypes eIndex) const;
	void changeProfessionCombatChange(ProfessionTypes eIndex, int iChange);
	int getProfessionMoveChange(ProfessionTypes eIndex) const;
	void changeProfessionMoveChange(ProfessionTypes eIndex, int iChange);
	int getBuildingClassCount(BuildingClassTypes eIndex) const;
	void changeBuildingClassCount(BuildingClassTypes eIndex, int iChange);
	int getBuildingClassMaking(BuildingClassTypes eIndex) const;
	void changeBuildingClassMaking(BuildingClassTypes eIndex, int iChange);
	int getBuildingClassCountPlusMaking(BuildingClassTypes eIndex) const;
	int getHurryCount(HurryTypes eIndex) const;
	bool canPopRush();
	void changeHurryCount(HurryTypes eIndex, int iChange);
	int getSpecialBuildingNotRequiredCount(SpecialBuildingTypes eIndex) const;
	bool isSpecialBuildingNotRequired(SpecialBuildingTypes eIndex) const;
	void changeSpecialBuildingNotRequiredCount(SpecialBuildingTypes eIndex, int iChange);
	DllExport CivicTypes getCivic(CivicOptionTypes eIndex) const;
	DllExport void setCivic(CivicOptionTypes eIndex, CivicTypes eNewValue);
	int getImprovementYieldChange(ImprovementTypes eIndex1, YieldTypes eIndex2) const;
	void changeImprovementYieldChange(ImprovementTypes eIndex1, YieldTypes eIndex2, int iChange);
	DllExport int getBuildingYieldChange(BuildingClassTypes eBuildingClass, YieldTypes eYield) const;
	void changeBuildingYieldChange(BuildingClassTypes eBuildingClass, YieldTypes eYield, int iChange);
	int getTaxYieldModifierCount(YieldTypes eYield) const;
	void changeTaxYieldModifierCount(YieldTypes eYield, int iChange) const;

	void updateGroupCycle(CvUnit* pUnit);
	void removeGroupCycle(int iID);

	CLLNode<int>* deleteGroupCycleNode(CLLNode<int>* pNode);
	CLLNode<int>* nextGroupCycleNode(CLLNode<int>* pNode) const;
	CLLNode<int>* previousGroupCycleNode(CLLNode<int>* pNode) const;
	CLLNode<int>* headGroupCycleNode() const;
	CLLNode<int>* tailGroupCycleNode() const;
	void addCityName(const CvWString& szName);
	int getNumCityNames() const;
	const CvWString& getCityName(int iIndex) const;

	// city iteration
	DllExport CvCity* firstCity(int *pIterIdx, bool bRev=false) const;
	DllExport CvCity* nextCity(int *pIterIdx, bool bRev=false) const;
	DllExport int getNumCities() const;
	DllExport CvCity* getCity(int iID) const;
	CvCity* addCity();
	void deleteCity(int iID);

	// unit iteration
	DllExport CvUnit* firstUnit(int *pIterIdx) const;
	DllExport CvUnit* nextUnit(int *pIterIdx) const;
	DllExport int getNumUnits() const;
	DllExport CvUnit* getUnit(int iID) const;
	CvUnit* addUnit();
	void addExistingUnit(CvUnit *pUnit);
	void deleteUnit(int iID);
	CvUnit* getAndRemoveUnit(int iId);

	int getNumEuropeUnits() const;
	CvUnit* getEuropeUnit(int iIndex) const;
	DllExport CvUnit* getEuropeUnitById(int iId) const;
	void loadUnitFromEurope(CvUnit* pUnit, CvUnit* pTransport);
	void unloadUnitToEurope(CvUnit* pUnit);
	void transferUnitInEurope(CvUnit* pUnit, CvUnit* pTransport);
	void doREFReduction(int iGold);

	int countNumTravelUnits(UnitTravelStates eState, DomainTypes eDomain) const;
	int countNumDomainUnits(DomainTypes eDomain) const;

	// selection groups iteration
	DllExport CvSelectionGroup* firstSelectionGroup(int *pIterIdx, bool bRev=false) const;
	DllExport CvSelectionGroup* nextSelectionGroup(int *pIterIdx, bool bRev=false) const;
	int getNumSelectionGroups() const;
	CvSelectionGroup* getSelectionGroup(int iID) const;
	CvSelectionGroup* addSelectionGroup();
	void deleteSelectionGroup(int iID);
	// pending triggers iteration
	EventTriggeredData* firstEventTriggered(int *pIterIdx, bool bRev=false) const;
	EventTriggeredData* nextEventTriggered(int *pIterIdx, bool bRev=false) const;
	int getNumEventsTriggered() const;
	EventTriggeredData* getEventTriggered(int iID) const;
	EventTriggeredData* addEventTriggered();
	void deleteEventTriggered(int iID);
	EventTriggeredData* initTriggeredData(EventTriggerTypes eEventTrigger, bool bFire = false, int iCityId = -1, int iPlotX = INVALID_PLOT_COORD, int iPlotY = INVALID_PLOT_COORD, PlayerTypes eOtherPlayer = NO_PLAYER, int iOtherPlayerCityId = -1, int iUnitId = -1, BuildingTypes eBuilding = NO_BUILDING);
	int getEventTriggerWeight(EventTriggerTypes eTrigger) const;
	DllExport void addMessage(const CvTalkingHeadMessage& message);
	void showMissedMessages();
	void clearMessages();
	DllExport const CvMessageQueue& getGameMessages() const;
	DllExport void expireMessages();
	DllExport void addPopup(CvPopupInfo* pInfo, bool bFront = false);
	void clearPopups();
	DllExport CvPopupInfo* popFrontPopup();
	DllExport const CvPopupQueue& getPopups() const;
	DllExport void addDiplomacy(CvDiploParameters* pDiplo);
	void clearDiplomacy();
	DllExport const CvDiploQueue& getDiplomacy() const;
	DllExport CvDiploParameters* popFrontDiplomacy();

	int getScoreHistory(int iTurn) const;
	void updateScoreHistory(int iTurn, int iBestScore);

	int getEconomyHistory(int iTurn) const;
	void updateEconomyHistory(int iTurn, int iBestEconomy);
	int getIndustryHistory(int iTurn) const;
	void updateIndustryHistory(int iTurn, int iBestIndustry);
	int getAgricultureHistory(int iTurn) const;
	void updateAgricultureHistory(int iTurn, int iBestAgriculture);
	int getPowerHistory(int iTurn) const;
	void updatePowerHistory(int iTurn, int iBestPower);
	int getCultureHistory(int iTurn) const;
	void updateCultureHistory(int iTurn, int iBestCulture);

	int addTradeRoute(const IDInfo& kSource, const IDInfo& kDestination, YieldTypes eYield);
	bool editTradeRoute(int iId, const IDInfo& kSource, const IDInfo& kDestination, YieldTypes eYield);
	bool removeTradeRoute(int iId);
	CvTradeRoute* getTradeRoute(int iId) const;
	int getNumTradeRoutes() const;
	CvTradeRoute* getTradeRouteByIndex(int iIndex) const;
	void getTradeRoutes(std::vector<CvTradeRoute*>& aTradeRoutes) const;
	void validateTradeRoutes();
	bool canLoadYield(PlayerTypes eCityPlayer) const;
	bool canUnloadYield(PlayerTypes eCityPlayer) const;

	// Script data needs to be a narrow string for pickling in Python
	std::string getScriptData() const;
	void setScriptData(std::string szNewValue);
	DllExport const CvString& getPbemEmailAddress() const;
	DllExport void setPbemEmailAddress(const char* szAddress);
	DllExport const CvString& getSmtpHost() const;
	DllExport void setSmtpHost(const char* szHost);
	const EventTriggeredData* getEventOccured(EventTypes eEvent) const;
	bool isTriggerFired(EventTriggerTypes eEventTrigger) const;
	void setEventOccured(EventTypes eEvent, const EventTriggeredData& kEventTriggered, bool bOthers = true);
	void resetEventOccured(EventTypes eEvent, bool bAnnounce = true);
	void setTriggerFired(const EventTriggeredData& kTriggeredData, bool bOthers = true, bool bAnnounce = true);
	void resetTriggerFired(EventTriggerTypes eEventTrigger);
	void trigger(EventTriggerTypes eEventTrigger);
	void trigger(const EventTriggeredData& kData);
	DllExport void applyEvent(EventTypes eEvent, int iTriggeredId, bool bUpdateTrigger = true);
	bool canDoEvent(EventTypes eEvent, const EventTriggeredData& kTriggeredData) const;
	int getEventCost(EventTypes eEvent, PlayerTypes eOtherPlayer, bool bRandom) const;
	bool canTrigger(EventTriggerTypes eTrigger, PlayerTypes ePlayer) const;
	const EventTriggeredData* getEventCountdown(EventTypes eEvent) const;
	void setEventCountdown(EventTypes eEvent, const EventTriggeredData& kEventTriggered);
	void resetEventCountdown(EventTypes eEvent);

	bool isFreePromotion(UnitCombatTypes eUnitCombat, PromotionTypes ePromotion) const;
	void setFreePromotion(UnitCombatTypes eUnitCombat, PromotionTypes ePromotion, bool bFree);
	bool isFreePromotion(UnitClassTypes eUnitCombat, PromotionTypes ePromotion) const;
	void setFreePromotion(UnitClassTypes eUnitCombat, PromotionTypes ePromotion, bool bFree);

	void invalidatePopulationRankCache();
	void invalidateYieldRankCache(YieldTypes eYield = NO_YIELD);

	PlayerTypes pickConqueredCityOwner(const CvCity& kCity) const;
	void forcePeace(PlayerTypes ePlayer);
	bool canSpiesEnterBorders(PlayerTypes ePlayer) const;
	int getNewCityProductionValue() const;

	int getGrowthThreshold(int iPopulation) const;

	void verifyUnitStacksValid();

	DllExport void buildTradeTable(PlayerTypes eOtherPlayer, CLinkList<TradeData>& ourList, const IDInfo& kTransport) const;
	DllExport bool getHeadingTradeString(PlayerTypes eOtherPlayer, TradeableItems eItem, CvWString& szString, CvString& szIcon) const;
	DllExport bool getItemTradeString(PlayerTypes eOtherPlayer, bool bOffer, bool bShowingCurrent, const TradeData& zTradeData, const IDInfo& kTransport, CvWString& szString, CvString& szIcon) const;
	DllExport void updateTradeList(PlayerTypes eOtherPlayer, CLinkList<TradeData>& ourInventory, const CLinkList<TradeData>& ourOffer, const CLinkList<TradeData>& theirOffer, const IDInfo& kTransport) const;
	DllExport int getMaxGoldTrade(PlayerTypes eOtherPlayer, const IDInfo& kTransport) const;

	CvCity* getPopulationUnitCity(int iUnitId) const;
	int getCrossesStored() const;
	void changeCrossesStored(int iChange);
	int getBellsStored() const;
	void changeBellsStored(int iChange);
	int getTaxRate() const;
	void setTaxRate(int iValue);
	void changeTaxRate(int iChange);
	int getNativeCombatModifier() const;
	void setNativeCombatModifier(int iValue);
	void changeNativeCombatModifier(int iChange);
	int getDominateNativeBordersCount() const;
	void changeDominateNativeBordersCount(int iChange);
	int getRevolutionEuropeTradeCount() const;
	void changeRevolutionEuropeTradeCount(int iChange);
	bool canTradeWithEurope() const;
	void interceptEuropeUnits();

	///TKs Invention Core Mod v 1.0
	int getVictoryYieldCount(YieldTypes eYield) const;
	void setVictoryYieldCount(YieldTypes eYield, int iValue);
	int getIdeaProgress(CivicTypes eCivic) const;
	void setIdeaProgress(CivicTypes eCivic, int iValue);
	void changeIdeaProgress(CivicTypes eCivic, int iChange);


    UnitTypes getDefaultPopUnit() const;
    void setDefaultPopUnit(UnitTypes eUnit);
	bool getTechsInitialized() const;
	///TKs Med
	DllExport CvCity* getTradeFairCity() const;
	void setTradeFairCity(CvCity* pTradeFairCity);
	bool canMakeVassalDemand(PlayerTypes eVassal);
	DllExport PlayerTypes getVassalOwner() const;
	DllExport PlayerTypes getMinorVassal() const;
	DllExport void setVassalOwner(PlayerTypes eParent);
	DllExport void setMinorVassal(PlayerTypes eParent);
	int getMultiYieldRate(YieldTypes eIndex) const;
	int getCensureType(CensureType eCensure) const;
	CvPlot* getStartingTradeRoutePlot(EuropeTypes eTradeRoute) const;
	void setStartingTradeRoutePlot(CvPlot* pNewValue, EuropeTypes eTradeRoute);
	void changeCensureType(CensureType eCensure, int iValue);
	bool getHasTradeRouteType(EuropeTypes eTradeRoute) const;
	void setHasTradeRouteType(EuropeTypes eTradeRoute, bool bValue);
	CvCity* findImmigrationCity(CvCity* pPrimaryCity, int MaxDistance);
	void doMedievalEvents();
	bool canUnitBeTraded(YieldTypes eYield, EuropeTypes eTradeScreen = NO_EUROPE, UnitTypes eUnit = NO_UNIT) const;
	bool isAllResearchComplete() const;
	void setAllResearchComplete(bool bSet);
	bool isFirstCityRazed() const;
	void setFirstCityRazed(bool iValue);
	void setTechsInitialized(bool bSet);
	int getFreeTechs() const;
	void changeFreeTechs(int iChange);
	int getDoTechFlag() const;
	void changeDoTechFlag(int iChange);
	int getEventResetTimer() const;
	void setCurrentFoundCityType(int iChange);
	int getCurrentFoundCityType() const;
	void changeEventResetTimer(int iChange);
	int getGoldPlundered() const;
	int getMissionsActive() const;
	int getVillages() const;
	int getMonasterys() const;
	int getCastles() const;
	int getNumDocksNextUnits() const;
	void changeGoldPlundered(int iChange);
	void changeMissionsActive(int iChange);
	void changeVillages(int iChange);
	void changeMonasterys(int iChange);
	void changeCastles(int iChange);
	void changeNumDocksNextUnits(int iChange);
	MedCityTypes getAICityType();
	void changeCityTypes(MedCityTypes CityType, int iChange);
	int prolificInventorThreshold() const;
    int getIdeasExperience() const;
    void changeProlificInventorModifier(int iChange);
    int getProlificInventorModifier() const;
    void changeProlificInventorThresholdModifier(int iChange);
    int getProlificInventorThresholdModifier() const;
	void setIdeasExperience(int iExperience);
    void createProlificInventor(UnitTypes eInvetorUnit, bool bIncrementExperience, int iX, int iY);
	int getCostToResearch(CivicTypes eCivic);
	int getPreviousFatherPoints(FatherPointTypes eIndex) const;
	int getTemporyIdeasStored() const;
	int getIdeasStored() const;
	void setPreviousFatherPoints(FatherPointTypes eIndex, int iChange);
	void setTemporyIdeasStored(int iValue);
	void changeIdeasStored(int iChange);
	void doSetupIdeas(bool Cheat=false);
	void doIdeas(bool Cheat=false);
	CivicTypes getCurrentResearch() const;
	CivicTypes getCurrentTradeResearch() const;
	void setCurrentResearch(CivicTypes eCurrentResearch);
	void setCurrentTradeResearch(CivicTypes eCurrentResearch);
	int getIdeasResearched(CivicTypes eIndex) const;
	// invention effect cache - start - Nightinggale
	//void changeIdeasResearched(CivicTypes eIndex, int iChange);
	void changeIdeasResearched(CivicTypes eIndex, int iChange, bool bUpdateCache = true);
	// invention effect cache - end - Nightinggale
	int getCurrentResearchProgress(bool bGetTurns, CivicTypes eCivic = NO_CIVIC);
	int getTurnstoCompleteResearch(bool bReturnNetResearch=false, CivicTypes eCivic = NO_CIVIC);
	void processCivics(CivicTypes eCivic, int iChange);
	int getIdea(bool Research, PlayerTypes ePlayer = NO_PLAYER) const;
	void setResearchPartner(PlayerTypes ePartner);
	PlayerTypes getResearchPartner() const;
	void cancelResearchPact(TeamTypes eEndingTeam);

	void ConvertUnits(UnitTypes eFromUnit, UnitTypes eToUnit, CivicTypes eCivic, int iFlag1 = -1, int iFlag2 = -1, int iFlag3 = -1);
    DllExport const wchar* getAttackForceKey() const;
    DllExport const wchar* getDeclareKey() const;
    DllExport const wchar* getDawnKey() const;
	///TKe
	///TKs Med
	int getSellToEuropeProfit(YieldTypes eYield, int iAmount, EuropeTypes eTradeScreen = NO_EUROPE) const;
	int getYieldSellPrice(YieldTypes eYield, EuropeTypes eTradeScreen = NO_EUROPE) const;
	int getYieldBuyPrice(YieldTypes eYield, EuropeTypes eTradeScreen = NO_EUROPE) const;
	int getTradeScreenPriceMod(YieldTypes eYield, EuropeTypes eTradeScreen = NO_EUROPE, UnitTypes eUnit = NO_UNIT) const;
	CvUnit* buyEuropeUnit(UnitTypes eUnit, int iPriceModifier, EuropeTypes eTradeScreen=NO_EUROPE);
	int getEuropeUnitBuyPrice(UnitTypes eUnit, EuropeTypes eTradeScreenType=NO_EUROPE) const;
	///TKe
	void setYieldBuyPrice(YieldTypes eYield, int iPrice, bool bMessage);
	void sellYieldUnitToEurope(CvUnit* pUnit, int iAmount, int iCommission);
	CvUnit* buyYieldUnitFromEurope(YieldTypes eYield, int iAmount, CvUnit* pTransport);
	void buyUnitsFromKing();
	int getYieldTradedTotal(YieldTypes eYield) const;
	void setYieldTradedTotal(YieldTypes eYield, int iValue);
	void changeYieldTradedTotal(YieldTypes eYield, int iChange);
	int getYieldBoughtTotal(YieldTypes eYield) const;
	void setYieldBoughtTotal(YieldTypes eYield, int iValue);
	void changeYieldBoughtTotal(YieldTypes eYield, int iChange);
	YieldTypes getHighestTradedYield() const;
	int getHighestStoredYieldCityId(YieldTypes eYield) const;

	DllExport void doAction(PlayerActionTypes eAction, int iData1, int iData2, int iData3);
	DllExport int getTradeYieldAmount(YieldTypes eYield, CvUnit* pTransport) const;
	DllExport void setCityBillboardDirty(bool bNewValue);
	DllExport bool isEurope() const;
	DllExport bool isInRevolution() const;
	bool checkIndependence() const;

	void applyMissionaryPoints(CvCity* pCity);
	int getMissionaryPoints(PlayerTypes ePlayer) const;
	void changeMissionaryPoints(PlayerTypes ePlayer, int iChange);
	int getMissionaryThresholdMultiplier(PlayerTypes ePlayer) const;
	void setMissionaryThresholdMultiplier(PlayerTypes ePlayer, int iValue);
	int missionaryThreshold(PlayerTypes ePlayer) const;
	void burnMissions(PlayerTypes ePlayer);
	bool canHaveMission(PlayerTypes ePlayer) const;
	void validateMissions();
	int getMissionaryRateModifier() const;
	void changeMissionaryRateModifier(int iChange);
	int getMissionarySuccessPercent() const;
	void setMissionarySuccessPercent(int iValue);

	int getRebelCombatPercent() const;

	int getProfessionEquipmentModifier(ProfessionTypes eProfession) const;
	void setProfessionEquipmentModifier(ProfessionTypes eProfession, int iValue);
	// cache CvPlayer::getYieldEquipmentAmount - start - Nightinggale
	ProfessionYieldCost getYieldEquipmentAmount(ProfessionTypes eProfession, YieldTypes eYield) const;
	bool hasContentsYieldEquipmentAmount(ProfessionTypes eProfession) const;
	ProfessionYieldCost getYieldEquipmentAmountSecure(ProfessionTypes eProfession, YieldTypes eYield) const;
	bool hasContentsYieldEquipmentAmountSecure(ProfessionTypes eProfession) const;
	bool hasContentsAltYieldEquipmentAmountSecure(ProfessionTypes eProfession) const;
	bool hasContentsAnyYieldEquipmentAmount(ProfessionTypes eProfession) const;
	bool hasContentsAnyYieldEquipmentAmountSecure(ProfessionTypes eProfession) const;
	// cache CvPlayer::getYieldEquipmentAmount - end - Nightinggale
	bool isProfessionValid(ProfessionTypes eProfession, UnitTypes eUnit) const;
	void changeProfessionEurope(int iUnitId, ProfessionTypes eProfession);

	int getNumRevolutionEuropeUnits() const;
	UnitTypes getRevolutionEuropeUnit(int i) const;
	ProfessionTypes getRevolutionEuropeProfession(int i) const;
	void addRevolutionEuropeUnit(UnitTypes eUnit, ProfessionTypes eProfession);
	void clearRevolutionEuropeUnits();

	UnitTypes getDocksNextUnit(int i) const;
	UnitTypes pickBestImmigrant();
	bool canHurry(HurryTypes eHurry, int iIndex) const;
	void hurry(HurryTypes eHurry, int iIndex);
	int getHurryGold(HurryTypes eHurry, int iIndex) const;
	const wchar* getHurryItemTextKey(HurryTypes eHurry, int iData) const;
	///TKs Invention Core Mod v 1.0
	void doImmigrant(int iIndex, int iReason = 0);
	///TKe

	void buyLand(CvPlot* pPlot, bool bFree);

	int getNumTradeMessages() const;
	const wchar* getTradeMessage(int i) const;

	virtual void AI_init() = 0;
	virtual void AI_reset() = 0;
	virtual void AI_doTurnPre() = 0;
	virtual void AI_doTurnPost() = 0;
	virtual void AI_doTurnUnitsPre() = 0;
	virtual void AI_doTurnUnitsPost() = 0;
	virtual void AI_updateFoundValues(bool bStartingLoc = false) = 0;
	virtual void AI_unitUpdate() = 0;
	virtual void AI_makeAssignWorkDirty() = 0;
	virtual void AI_assignWorkingPlots() = 0;
	virtual void AI_updateAssignWork() = 0;
	virtual void AI_makeProductionDirty() = 0;
	virtual void AI_conquerCity(CvCity* pCity) = 0;
	virtual int AI_foundValue(int iX, int iY, int iMinUnitRange = -1, bool bStartingLoc = false) = 0;
	virtual int AI_getPlotDanger(CvPlot* pPlot, int iRange = -1, bool bTestMoves = true, bool bOffensive = false) = 0;
	virtual bool AI_isWillingToTalk(PlayerTypes ePlayer) = 0;
	virtual bool AI_demandRebukedSneak(PlayerTypes ePlayer) = 0;
	virtual bool AI_demandRebukedWar(PlayerTypes ePlayer) = 0;
	virtual AttitudeTypes AI_getAttitude(PlayerTypes ePlayer, bool bForced = true) = 0;
	virtual int AI_dealVal(PlayerTypes ePlayer, const CLinkList<TradeData>* pList, bool bIgnoreAnnual = false, int iExtra = 0) = 0;
	virtual bool AI_considerOffer(PlayerTypes ePlayer, const CLinkList<TradeData>* pTheirList, const CLinkList<TradeData>* pOurList, int iChange = 1) = 0;
	virtual int AI_militaryHelp(PlayerTypes ePlayer, int& iNumUnits, UnitTypes& eUnit, ProfessionTypes& eProfession) = 0;
	virtual int AI_maxGoldTrade(PlayerTypes ePlayer) const = 0;
	virtual bool AI_counterPropose(PlayerTypes ePlayer, const CLinkList<TradeData>* pTheirList, const CLinkList<TradeData>* pOurList, CLinkList<TradeData>* pTheirInventory, CLinkList<TradeData>* pOurInventory, CLinkList<TradeData>* pTheirCounter, CLinkList<TradeData>* pOurCounter, const IDInfo& kTransport) = 0;
	virtual int AI_cityTradeVal(CvCity* pCity, PlayerTypes eOwner = NO_PLAYER) = 0;
	virtual DenialTypes AI_cityTrade(CvCity* pCity, PlayerTypes ePlayer) const = 0;
	virtual DenialTypes AI_stopTradingTrade(TeamTypes eTradeTeam, PlayerTypes ePlayer) const = 0;
	virtual DenialTypes AI_yieldTrade(YieldTypes eYield, const IDInfo& kTransport, PlayerTypes ePlayer) const = 0;
	virtual int AI_unitValue(UnitTypes eUnit, UnitAITypes eUnitAI, CvArea* pArea) = 0;
	virtual int AI_totalUnitAIs(UnitAITypes eUnitAI) = 0;
	virtual int AI_totalAreaUnitAIs(CvArea* pArea, UnitAITypes eUnitAI) = 0;
	virtual int AI_totalWaterAreaUnitAIs(CvArea* pArea, UnitAITypes eUnitAI) = 0;
	virtual int AI_plotTargetMissionAIs(CvPlot* pPlot, MissionAITypes eMissionAI, CvSelectionGroup* pSkipSelectionGroup = NULL, int iRange = 0) = 0;
	virtual int AI_unitTargetMissionAIs(CvUnit* pUnit, MissionAITypes eMissionAI, CvSelectionGroup* pSkipSelectionGroup = NULL) = 0;
	virtual int AI_civicValue(CivicTypes eCivic) = 0;
	virtual int AI_getNumAIUnits(UnitAITypes eIndex) = 0;
	virtual void AI_changePeacetimeTradeValue(PlayerTypes eIndex, int iChange) = 0;
	virtual void AI_changePeacetimeGrantValue(PlayerTypes eIndex, int iChange) = 0;
	virtual int AI_getAttitudeExtra(PlayerTypes eIndex) = 0;
	virtual void AI_setAttitudeExtra(PlayerTypes eIndex, int iNewValue) = 0;
	virtual void AI_changeAttitudeExtra(PlayerTypes eIndex, int iChange) = 0;
	virtual void AI_setFirstContact(PlayerTypes eIndex, bool bNewValue) = 0;
	virtual int AI_getMemoryCount(PlayerTypes eIndex1, MemoryTypes eIndex2) = 0;
	virtual void AI_changeMemoryCount(PlayerTypes eIndex1, MemoryTypes eIndex2, int iChange) = 0;
	virtual EventTypes AI_chooseEvent(int iTriggeredId) = 0;
	virtual void AI_doAdvancedStart(bool bNoExit = false) = 0;
	virtual int AI_getExtraGoldTarget() const = 0;
	virtual void AI_setExtraGoldTarget(int iNewValue) = 0;
	virtual void AI_chooseCivic(CivicOptionTypes eCivicOption) = 0;
	virtual bool AI_chooseGoody(GoodyTypes eGoody) = 0;
	virtual CvCity* AI_findBestCity() const = 0;
	virtual CvCity* AI_findBestPort() const = 0;

	bool checkPopulation() const;
	bool checkPower(bool bReset);

protected:

	int m_iStartingX;
	int m_iStartingY;
	int m_iTotalPopulation;
	int m_iTotalLand;
	int m_iTotalLandScored;
	int m_iGold;
	int m_iAdvancedStartPoints;
	int m_iGreatGeneralsCreated;
	int m_iGreatGeneralsThresholdModifier;
	int m_iGreatGeneralRateModifier;
	int m_iDomesticGreatGeneralRateModifier;
	int m_iImmigrationThresholdMultiplier;
	int m_iRevolutionEuropeUnitThresholdMultiplier;
	int m_iKingNumUnitMultiplier;
	int m_iNativeAngerModifier;
	int m_iFreeExperience;
	int m_iWorkerSpeedModifier;
	int m_iImprovementUpgradeRateModifier;
	int m_iMilitaryProductionModifier;
	int m_iCityDefenseModifier;
	int m_iHighestUnitLevel;
	int m_iFatherOverflowBells;
	int m_iExpInBorderModifier;
	int m_iLevelExperienceModifier;
	int m_iCapitalCityID;
	int m_iCitiesLost;
	int m_iAssets;
	int m_iPower;
	int m_iPopulationScore;
	int m_iLandScore;
	int m_iFatherScore;
	int m_iCombatExperience;
	int m_iPopRushHurryCount;
	int m_iCrossesStored;
	int m_iBellsStored;
	int m_iTaxRate;
	int m_iNativeCombatModifier;
	int m_iDominateNativeBordersCount;
	int m_iRevolutionEuropeTradeCount;
	int m_iFatherPointMultiplier;
	int m_iMissionaryRateModifier;
	int m_iMissionarySuccessPercent;
    ///TKs Invention Core Mod v 1.0
    int m_iTradeFairCityID;
    int m_iProlificInventorModifier;
	int m_iProlificInventorThresholdModifier;
	int m_iIdeasExperience;
	int m_iIdeasStored;
	int m_iDoTechFlag;
	int m_iEventResetTimer;
	int m_iCurrentFoundCityType;
	int m_iGoldPlundered;
	int m_iMissionsActive;
	int m_iVillages;
	int m_iMonasterys;
	int m_iCastles;
	int m_iNumDocksNextUnits;
	UnitTypes m_iDefaultPopUnit;
	int m_iFreeTechs;
	int m_bTechsInitialized;
	int m_bAllResearchComplete;
	int m_bFirstCityRazed;
	int m_iTemporyIdeasStored;
    CivicTypes m_eCurrentResearch;
    CivicTypes m_eCurrentTradeResearch;
    PlayerTypes m_eResearchPartner;
    PlayerTypes m_eVassal;
    PlayerTypes m_eMinorVassal;
	///TKe

	uint m_uiStartTime;  // XXX save these?

	bool m_bAlive;
	bool m_bEverAlive;
	bool m_bTurnActive;
	bool m_bAutoMoves;
	bool m_bEndTurn;
	bool m_bPbemNewTurn;
	bool m_bExtendedGame;
	bool m_bFoundedFirstCity;
	bool m_bStrike;
	bool m_bHuman;

	PlayerTypes m_eID;
	LeaderHeadTypes m_ePersonalityType;
	EraTypes m_eCurrentEra;
	PlayerTypes m_eParent;

	TeamTypes m_eTeamType;
	YieldTypes m_eImmigrationConversion;

	int* m_aiSeaPlotYield;
	int* m_aiYieldRateModifier;
	int* m_aiCapitalYieldRateModifier;
	int* m_aiBuildingRequiredYieldModifier;
	int* m_aiCityExtraYield;
	int* m_aiExtraYieldThreshold;
	int* m_aiYieldBuyPrice;
	int* m_aiYieldTradedTotal;
	int* m_aiYieldBoughtTotal;
	int* m_aiTaxYieldModifierCount;
	///TKs Invention Core Mod v 1.0
	int* m_aiVictoryYieldCount;
	int* m_aiCensureTypes;
	///TKs Med
	int* m_aiTradeRouteStartingPlotX;
	int* m_aiTradeRouteStartingPlotY;
	bool* m_abTradeRouteTypes;
	///Tke

	bool* m_abYieldEuropeTradable;
	bool* m_abFeatAccomplished;
	bool* m_abOptions;

	CvString m_szScriptData;
    ///TKs Invention Core Mod v 1.0
    int* m_aiIdeaProgress;
    int* m_aiIdeasResearched;
    int* m_aiPreviousFatherPoints;
    ///TKe
	int* m_paiImprovementCount;
	int* m_paiFreeBuildingCount;
	int* m_paiUnitClassCount;
	int* m_paiUnitClassMaking;
	int* m_paiUnitClassImmigrated;
	int* m_paiUnitMoveChange;
	int* m_paiUnitStrengthModifier;
	int* m_paiProfessionCombatChange;
	int* m_paiProfessionMoveChange;
	int* m_paiBuildingClassCount;
	int* m_paiBuildingClassMaking;
	int* m_paiHurryCount;
	int* m_paiSpecialBuildingNotRequiredCount;
	int* m_aiMissionaryPoints;
	int* m_aiMissionaryThresholdMultiplier;
	int* m_aiProfessionEquipmentModifier;
	int* m_aiTraitCount;

	// cache CvPlayer::getYieldEquipmentAmount - start - Nightinggale
	YieldArray<ProfessionYieldCost> *m_cache_YieldEquipmentAmount;
	void Update_cache_YieldEquipmentAmount();
	void Update_cache_YieldEquipmentAmount(ProfessionTypes eProfession);
	ProfessionYieldCost getYieldEquipmentAmountUncached(ProfessionTypes eProfession, YieldTypes eYield) const;
	// cache CvPlayer::getYieldEquipmentAmount - end - Nightinggale

	std::vector<EventTriggerTypes> m_triggersFired;
	CivicTypes* m_paeCivics;
	int** m_ppiImprovementYieldChange;
	int** m_ppiBuildingYieldChange;
	CLinkList<int> m_groupCycle;
	std::vector<CvWString> m_aszCityNames;
	FFreeListTrashArray<CvCityAI> m_cities;
	CvIdVector<CvTradeRoute> m_tradeRoutes;
	CvIdVector<CvUnitAI> m_units;
	std::vector<CvUnit*> m_aEuropeUnits;
	FFreeListTrashArray<CvSelectionGroupAI> m_selectionGroups;
	FFreeListTrashArray<EventTriggeredData> m_eventsTriggered;
	CvEventMap m_mapEventsOccured;
	CvEventMap m_mapEventCountdown;
	UnitCombatPromotionArray m_aFreeUnitCombatPromotions;
	UnitClassPromotionArray m_aFreeUnitClassPromotions;

	std::vector< std::pair<UnitTypes, ProfessionTypes> > m_aEuropeRevolutionUnits;
	std::vector<UnitTypes> m_aDocksNextUnits;
	CvMessageQueue m_listGameMessages;
	CvPopupQueue m_listPopups;
	CvDiploQueue m_listDiplomacy;
	CvTurnScoreMap m_mapScoreHistory;
	CvTurnScoreMap m_mapEconomyHistory;
	CvTurnScoreMap m_mapIndustryHistory;
	CvTurnScoreMap m_mapAgricultureHistory;
	CvTurnScoreMap m_mapPowerHistory;
	CvTurnScoreMap m_mapCultureHistory;
	std::vector<CvWString> m_aszTradeMessages;

	void doGold();
	void doBells();
	void doCrosses();
	/// PlotGroup - start - Nightinggale
	void doCities();
	/// PlotGroup - end - Nightinggale
	void doWarnings();
	void doEvents();
	void doPrices();

	bool checkExpireEvent(EventTypes eEvent, const EventTriggeredData& kTriggeredData) const;
	void expireEvent(EventTypes eEvent, const EventTriggeredData& kTriggeredData, bool bFail);
	CvCity* pickTriggerCity(EventTriggerTypes eTrigger) const;
	CvUnit* pickTriggerUnit(EventTriggerTypes eTrigger, CvPlot* pPlot, bool bPickPlot) const;
	void freeEuropeUnits();
    ///TKs Invention Core Mod v 1.0
	//void processCivics(CivicTypes eCivic, int iChange);
	///TKe

	// for serialization
	virtual void read(FDataStreamBase* pStream);
	virtual void write(FDataStreamBase* pStream);
	void doUpdateCacheOnTurn();

/// PlotGroup - start - Nightinggale
public:
	CvPlotGroup* firstPlotGroup(int *pIterIdx, bool bRev=false) const;
	CvPlotGroup* nextPlotGroup(int *pIterIdx, bool bRev=false) const;
	int getNumPlotGroups() const;
	CvPlotGroup* getPlotGroup(int iID) const;
	CvPlotGroup* addPlotGroup();
	void deletePlotGroup(int iID);
	CvPlotGroup* initPlotGroup(CvPlot* pPlot);

	// update the cache is needed
	void setPlotgroupCityCache();

	// mark the cities in plotgroup cache as outdated
	void clearPlotgroupCityCache();

	// get plotgroups in cache and update cache if needed
	int getNumPlotgroups();

	// number of cached cities in a cached plotgroup
	int getNumCitiesInPlotgroup(int iPlotGroup) const;

	// get city from cached plotgroups
	CvCity* getCity(int iPlotGroup, int iCity) const;

	// get cache index of a plotgroup nd update cache is needed
	int getCacheIndex(CvPlotGroup* pPlotGroup);

protected:
	FFreeListTrashArray<CvPlotGroup> m_plotGroups;

	std::vector<std::vector<CvCity*> > m_aapPlotGroupCityList;
	std::vector<CvPlotGroup*> m_aPlotGroupCache;
	bool m_bIsPlotGroupCacheUpdated;
/// PlotGroup - end - Nightinggale

// invention effect cache - start - Nightinggale
public:
	bool canUseYield(YieldTypes eYield) const;
	bool canUseUnit(UnitTypes eUnit) const;
	bool canUseBuilding(BuildingTypes eBuilding) const;
	bool canUseProfession(ProfessionTypes eProfession) const;
	bool canUseBonus(BonusTypes eBonus) const;
	int getCityPlotFoodBonus() const;

protected:
	YieldArray<bool> m_abBannedYields;
	UnitArray<bool> m_abBannedUnits;
	BuildingArray<bool> m_abBannedBuildings;
	ProfessionArray<bool> m_abBannedProfessions;
	BonusArray<bool> m_abBannedBonus;

	int m_iCityPlotFoodBonus;

	void updateInventionEffectCache();
// invention effect cache - end - Nightinggale

// transport feeder - start - Nightinggale
public:
	void updateTransportThreshold();
	void updateTransportThreshold(YieldTypes eYield);
// transport feeder - end - Nightinggale
};

// cache CvPlayer::getYieldEquipmentAmount - start - Nightinggale
inline ProfessionYieldCost CvPlayer::getYieldEquipmentAmount(ProfessionTypes eProfession, YieldTypes eYield) const
{
	FAssert(m_cache_YieldEquipmentAmount != NULL);
	FAssert(eProfession >= 0 && eProfession < GC.getNumProfessionInfos());
	return m_cache_YieldEquipmentAmount[eProfession].get(eYield);
}

inline bool CvPlayer::hasContentsYieldEquipmentAmount(ProfessionTypes eProfession) const
{
	// strictly speaking it returns true if the array is allocated without considering the content of the array.
	// The reason why it works is because Update_cache_YieldEquipmentAmount() will only allocate arrays if they contain anything
	//   and deallocate them if it is changed to contain only 0.
	FAssert(m_cache_YieldEquipmentAmount != NULL);
	FAssert(eProfession >= 0 && eProfession < GC.getNumProfessionInfos());
	return m_cache_YieldEquipmentAmount[eProfession].isAllocated();
}

// same functions, but with the added return 0 if professions is NO_PROFESSION or INVALID_PROFESSION
inline ProfessionYieldCost CvPlayer::getYieldEquipmentAmountSecure(ProfessionTypes eProfession, YieldTypes eYield) const
{
	return eProfession > NO_PROFESSION ? getYieldEquipmentAmount(eProfession, eYield) : 0;
}

inline bool CvPlayer::hasContentsYieldEquipmentAmountSecure(ProfessionTypes eProfession) const
{
	return eProfession > NO_PROFESSION ? hasContentsYieldEquipmentAmount(eProfession) : false;
}

// shortcut to check both normal and alt equipment
inline bool CvPlayer::hasContentsAnyYieldEquipmentAmount(ProfessionTypes eProfession) const
{
	return hasContentsAnyYieldEquipmentAmount(eProfession) || hasContentsAnyYieldEquipmentAmount(eProfession);
}

inline bool CvPlayer::hasContentsAnyYieldEquipmentAmountSecure(ProfessionTypes eProfession) const
{
	return hasContentsAnyYieldEquipmentAmountSecure(eProfession) || hasContentsAnyYieldEquipmentAmountSecure(eProfession);
}
// cache CvPlayer::getYieldEquipmentAmount - end - Nightinggale

// invention effect cache - start - Nightinggale
inline bool CvPlayer::canUseYield(YieldTypes eYield) const
{
	FAssert(eYield < NUM_YIELD_TYPES);
	return eYield >= 0 ? !this->m_abBannedYields.get(eYield) : false;
}

inline bool CvPlayer::canUseUnit(UnitTypes eUnit) const
{
	FAssert(eUnit < GC.getNumUnitInfos());
	return eUnit >= 0 ? !this->m_abBannedUnits.get(eUnit) : false;
}

inline bool CvPlayer::canUseBuilding(BuildingTypes eBuilding) const
{
	return eBuilding >= 0 ? !this->m_abBannedBuildings.get(eBuilding) : false;
}

inline bool CvPlayer::canUseProfession(ProfessionTypes eProfession) const
{
	FAssert(eProfession < GC.getNumProfessionInfos());
	return eProfession >= 0 ? !this->m_abBannedProfessions.get(eProfession) : false;
}

inline bool CvPlayer::canUseBonus(BonusTypes eBonus) const
{
	return eBonus >= 0 ? !m_abBannedBonus.get(eBonus) : false;
}

inline int CvPlayer::getCityPlotFoodBonus() const
{
	return m_iCityPlotFoodBonus;
}
// invention effect cache - end - Nightinggale

/// PlotGroup - start - Nightinggale
inline CvPlotGroup* CvPlayer::firstPlotGroup(int *pIterIdx, bool bRev) const
{
	return !bRev ? m_plotGroups.beginIter(pIterIdx) : m_plotGroups.endIter(pIterIdx);
}

inline CvPlotGroup* CvPlayer::nextPlotGroup(int *pIterIdx, bool bRev) const
{
	return !bRev ? m_plotGroups.nextIter(pIterIdx) : m_plotGroups.prevIter(pIterIdx);
}

inline int CvPlayer::getNumPlotGroups() const																		
{
	return m_plotGroups.getCount();
}

inline CvPlotGroup* CvPlayer::getPlotGroup(int iID) const															
{
	return((CvPlotGroup *)(m_plotGroups.getAt(iID)));
}

inline CvPlotGroup* CvPlayer::addPlotGroup()																	
{
	return((CvPlotGroup *)(m_plotGroups.add()));
}

inline void CvPlayer::deletePlotGroup(int iID)																
{
	m_plotGroups.removeAt(iID);
}

inline void CvPlayer::clearPlotgroupCityCache()
{
	this->m_bIsPlotGroupCacheUpdated = false;
}
/// PlotGroup - end - Nightinggale

#endif
