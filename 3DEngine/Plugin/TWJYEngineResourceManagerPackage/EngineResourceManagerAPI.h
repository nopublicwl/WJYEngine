/*
 * EngineResourceManagerAPI.h
 *
 *  Created on: 2009-10-26
 *      Author: Administrator
 */
#include "TWJYEngineResourceManagerPKH.h"
#include "EngineResourceManagerInface.h"
#ifndef ENGINERESOURCEMANAGERAPI_H_
#define ENGINERESOURCEMANAGERAPI_H_
	extern WJYLibraryHandle g_hLibraryHandle_Resource;
	_CallStack_default_ uintV_WJY __native_hash(const_WJY char_WJY * ptrKey,intV_WJY iSize,intV_WJY iRange);

	_CallStack_default_ HPolygonMgrAndle 		Eg_CreatePolygonManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_WJY 		 		Eg_DestoryPolygonManager(HPolygonMgrAndle hAndle);
	_CallStack_default_ WJY_ResourcePolygon *    Eg_CreatePolygonMgrObject(HPolygonMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ WJY_ResourcePolygon *    Eg_OpenPolygonMgrObject(HPolygonMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result			    Eg_ReleasePolygonMgrObject(WJY_ResourcePolygon * ptrItem);
	_CallStack_default_ HWJY_Result			    Eg_DestoryPolygonMgrObject(HPolygonMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_	HWJY_Result              Eg_PushPolygonRTaskerQueue(WJY_ResourcePolygon * ptrItem);
	_CallStack_default_ HWJY_Result              Eg_PushPolygonRTaskerQueueFill(WJY_ResourcePolygon * ptrItem,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_	HWJY_Result              Eg_PushPolygonRTaskerQueueN(HPolygonMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result 				Eg_PushPolygonRTaskerQueueNFill(HPolygonMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_ HWJY_Result              Eg_RefurbishPolygonRBackgroundDispose(HPolygonMgrAndle hAndle,WJY_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HTextureMgrAndle 		Eg_CreateTextureManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_WJY 		 		Eg_DestoryTextureManager(HTextureMgrAndle hAndle);
	_CallStack_default_ WJY_ResourceTexture *    Eg_CreateTextureMgrObject(HTextureMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ WJY_ResourceTexture *    Eg_OpenTextureMgrObject(HTextureMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result			    Eg_ReleaseTextureMgrObject(WJY_ResourceTexture * ptrItem);
	_CallStack_default_ HWJY_Result			    Eg_DestoryTextureMgrObject(HTextureMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_	HWJY_Result              Eg_PushTextureRTaskerQueue(WJY_ResourceTexture * ptrItem);
	_CallStack_default_ HWJY_Result              Eg_PushTextureRTaskerQueueFill(WJY_ResourcePolygon * ptrItem,lint_WJY lMov,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_	HWJY_Result              Eg_PushTextureRTaskerQueueN(HPolygonMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result 				Eg_PushTextureRTaskerQueueNFill(HPolygonMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_ HWJY_Result              Eg_RefurbishTextureRBackgroundDispose(HTextureMgrAndle hAndle,WJY_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HScriptMgrAndle			Eg_CreateScriptManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_WJY					Eg_DestoryScriptManager(HScriptMgrAndle hAndle);
	_CallStack_default_ WJY_ResourceScript  *    Eg_CreateScriptMgrObject(HScriptMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ WJY_ResourceScript  *    Eg_OpenScriptMgrObject(HScriptMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result			    Eg_ReleaseScriptMgrObject(WJY_ResourceScript * ptrItem);
	_CallStack_default_ HWJY_Result			    Eg_DestoryScriptMgrObject(HScriptMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_	HWJY_Result              Eg_PushScriptRTaskerQueue(WJY_ResourceScript * ptrItem);
	_CallStack_default_ HWJY_Result              Eg_PushScriptRTaskerQueueFill(WJY_ResourcePolygon * ptrItem,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_	HWJY_Result              Eg_PushScriptRTaskerQueueN(HScriptMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result 				Eg_PushScriptRTaskerQueueNFill(HPolygonMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_ HWJY_Result              Eg_RefurbishScriptRBackgroundDispose(HScriptMgrAndle hAndle,WJY_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HMaterialMgrAndle 		Eg_CreateMaterialManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_WJY 		 		Eg_DestoryMaterialManager(HMaterialMgrAndle hAndle);
	_CallStack_default_ WJY_ResourceMaterial *   Eg_CreateMaterialMgrObject(HMaterialMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ WJY_ResourceMaterial *   Eg_OpenMaterialMgrObject(HMaterialMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result			    Eg_ReleaseMaterialMgrObject(WJY_ResourceMaterial * ptrItem);
	_CallStack_default_ HWJY_Result			    Eg_DestoryMaterialMgrObject(HMaterialMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_	HWJY_Result              Eg_PushMaterialRTaskerQueue(WJY_ResourceMaterial * ptrItem);
	_CallStack_default_ HWJY_Result              Eg_PushMaterialRTaskerQueueFill(WJY_ResourceMaterial * ptrItem,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_	HWJY_Result              Eg_PushMaterialRTaskerQueueN(HMaterialMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result 				Eg_PushMaterialRTaskerQueueNFill(HMaterialMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_ HWJY_Result              Eg_RefurbishMaterialRBackgroundDispose(HMaterialMgrAndle hAndle,WJY_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HVideoMgrAndle	 		Eg_CreateVideoManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_WJY 		 		Eg_DestoryVideoManager(HVideoMgrAndle hAndle);
	_CallStack_default_ WJY_ResourceVideo *   	Eg_CreateVideoMgrObject(HVideoMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ WJY_ResourceVideo *    	Eg_OpenVideoMgrObject(HVideoMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result			    Eg_ReleaseVideoMgrObject(WJY_ResourceVideo * ptrItem);
	_CallStack_default_ HWJY_Result			    Eg_DestoryVideoMgrObject(HVideoMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_	HWJY_Result              Eg_PushVideoRTaskerQueue(WJY_ResourceVideo * ptrItem);
	_CallStack_default_ HWJY_Result              Eg_PushVideoRTaskerQueueFill(WJY_ResourceVideo * ptrItem,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_	HWJY_Result              Eg_PushVideoRTaskerQueueN(HVideoMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result 				Eg_PushVideoRTaskerQueueNFill(HVideoMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_ HWJY_Result              Eg_RefurbishVideoRBackgroundDispose(HVideoMgrAndle hAndle,WJY_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HWaveMgrAndle	 		Eg_CreateWaveManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_WJY 		 		Eg_DestoryWaveManager(HWaveMgrAndle hAndle);
	_CallStack_default_ WJY_ResourceWave *   	Eg_CreateWaveMgrObject(HWaveMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ WJY_ResourceWave *    	Eg_OpenWaveMgrObject(HWaveMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result			    Eg_ReleaseWaveMgrObject(WJY_ResourceWave * ptrItem);
	_CallStack_default_ HWJY_Result			    Eg_DestoryWaveMgrObject(HWaveMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_	HWJY_Result              Eg_PushWaveRTaskerQueue(WJY_ResourceWave * ptrItem);
	_CallStack_default_ HWJY_Result              Eg_PushWaveRTaskerQueueFill(WJY_ResourceWave * ptrItem,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_	HWJY_Result              Eg_PushWaveRTaskerQueueN(HWaveMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result 				Eg_PushWaveRTaskerQueueNFill(HWaveMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_ HWJY_Result              Eg_RefurbishWaveRBackgroundDispose(HWaveMgrAndle hAndle,WJY_ResourceBgDisposeParamer * ptrParamer);

	_CallStack_default_ HSoundMgrAndle	 		Eg_CreateSoundManager(HResDataSystem hRDSystem);
	_CallStack_default_ void_WJY 		 		Eg_DestorySoundManager(HSoundMgrAndle hAndle);
	_CallStack_default_ WJY_ResourceSound *   	Eg_CreateSoundMgrObject(HSoundMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ WJY_ResourceSound *    	Eg_OpenSoundMgrObject(HSoundMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result			    Eg_ReleaseSoundMgrObject(WJY_ResourceSound * ptrItem);
	_CallStack_default_ HWJY_Result			    Eg_DestorySoundMgrObject(HSoundMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_	HWJY_Result              Eg_PushSoundRTaskerQueue(WJY_ResourceSound * ptrItem);
	_CallStack_default_ HWJY_Result              Eg_PushSoundRTaskerQueueFill(WJY_ResourceSound * ptrItem,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_	HWJY_Result              Eg_PushSoundRTaskerQueueN(HSoundMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize);
	_CallStack_default_ HWJY_Result 				Eg_PushSoundRTaskerQueueNFill(HSoundMgrAndle hAndle,const_WJY char_WJY * ptrKey,intV_WJY iKeySize,WJY_CommResourceBlock * ptrBlock);
	_CallStack_default_ HWJY_Result              Eg_RefurbishSoundRBackgroundDispose(HSoundMgrAndle hAndle,WJY_ResourceBgDisposeParamer * ptrParamer);


					template<typename Mgr,typename Node>
						bool_WJY __native_Eg_PushPriorityStackSortList(Mgr * ptrMgr,Node * ptrItem,intV_WJY iMaxCount){
							intV_WJY iSerial;
							intV_WJY iPSerial;
							Node * ptrSWAP;
							if(ptrMgr->iTkCount>=iMaxCount){
								return false_WJY;
							}
							ptrMgr->TaskList[ptrMgr->iTkCount] = ptrItem;
							WJYSysAPI_Syn_AtomInterAdd(&(ptrMgr->iTkCount),1);
							//ptrMgr->iTkCount++;
							iSerial = ptrMgr->iTkCount;
							while(true_WJY){
								iPSerial = iSerial>>1;
								if((iSerial>>1)<=0)
									break;
								ptrSWAP = ptrMgr->TaskList[iPSerial - 1];
								if(ptrMgr->TaskList[iPSerial - 1]->iPRI>=ptrMgr->TaskList[iSerial - 1]->iPRI)
									break;
								ptrMgr->TaskList[iPSerial - 1] = ptrMgr->TaskList[iSerial - 1];
								ptrMgr->TaskList[iSerial - 1]  = ptrSWAP;
							}
							return true_WJY;
						}
					template<typename Mgr,typename Node>
						Node * __native_Eg_PopMaxPriorityStackSort(Mgr * ptrMgr){
							Node * ptrRNode;
							Node * ptrSwap;
							intV_WJY iSerial;
							intV_WJY iChildLSerial;
							intV_WJY iChildRSerial;
							intV_WJY iChildLIndex;
							intV_WJY iChildRIndex;
							intV_WJY iIndex;
							if(ptrMgr->iTkCount<=0)
								return NULL_WJY;
							ptrRNode = ptrMgr->TaskList[0];
							WJYSysAPI_Syn_AtomInterAdd(&(ptrMgr->iTkCount),-1);
							ptrMgr->TaskList[0] = ptrMgr->TaskList[ptrMgr->iTkCount];
							iSerial = 1;
							iIndex  = 0;
							while((iChildLSerial = (iSerial<<1)) <= ptrMgr->iTkCount){
								iChildRSerial =  (iSerial<<1) + 1;
								iChildLIndex  =  iChildLSerial - 1;
								iChildRIndex  =  iChildRSerial - 1;
								if((iChildRSerial <= ptrMgr->iTkCount) && (ptrMgr->TaskList[iChildRIndex]->iPRI > ptrMgr->TaskList[iChildLIndex]->iPRI)){
									iChildLSerial= iChildRSerial;
									iChildLIndex = iChildRIndex;
								}
								if(ptrMgr->TaskList[iIndex]->iPRI >= ptrMgr->TaskList[iChildLIndex]->iPRI)
									break;
								ptrSwap = ptrMgr->TaskList[iChildLIndex];
								ptrMgr->TaskList[iChildLIndex] = ptrMgr->TaskList[iIndex];
								ptrMgr->TaskList[iIndex] = ptrSwap;
								iSerial = iChildLSerial;
								iIndex  = iChildLIndex;
							}
							return ptrRNode;
						}
					template<typename Mgr,typename Node>
						Node * __native_Eg_RemoveMapItem(Mgr * ptrMgr,uintV_WJY uIndex,Node * ptrItem){
							Node * ptrPUpItem;
							Node * ptrPNItem;
							ptrPNItem = ptrMgr->List[uIndex].ptrRoot;
							ptrPUpItem= ptrMgr->List[uIndex].ptrRoot;
							while(ptrPNItem != NULL_WJY){
								if(ptrPNItem == ptrItem){
									if(ptrPNItem == ptrPUpItem){
										ptrMgr->List[uIndex].ptrRoot = ptrPNItem->ptrMNext;
									}else{
										ptrPUpItem->ptrMNext = ptrPNItem->ptrMNext;
									}
									WJYSysAPI_Syn_AtomInterAdd(&(ptrMgr->iCount),-1);
									//ptrPNItem->eDynamicState = WJYSys_Const_RODynamic_eReclaim;
									return ptrPNItem;
								}
								ptrPNItem = ptrPNItem->ptrMNext;
								ptrPUpItem= ptrPNItem;
							}
							return NULL_WJY;
						}
					//must remove
					template<typename Mgr,typename Node>
						Node * __native_Eg_RemoveMapItem(Mgr * ptrMgr,uintV_WJY uIndex,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
							Node * ptrPUpItem;
							Node * ptrPNItem;
							ptrPNItem = ptrMgr->List[uIndex].ptrRoot;
							ptrPUpItem= ptrMgr->List[uIndex].ptrRoot;
							while(ptrPNItem != NULL_WJY){
								if((iKeySize == ptrPNItem->iNSize) && (WJYSysAPI_MemoryCmp(ptrKey,ptrPNItem->ptrName,iKeySize) == 0)){
									if(ptrPNItem == ptrPUpItem){
										ptrMgr->List[uIndex].ptrRoot = ptrPNItem->ptrMNext;
									}else{
										ptrPUpItem->ptrMNext = ptrPNItem->ptrMNext;
									}
									WJYSysAPI_Syn_AtomInterAdd(&(ptrMgr->iCount),-1);
									ptrPNItem->eDynamicState = WJYSys_Const_RODynamic_eReclaim;
									return ptrPNItem;
								}
								ptrPNItem = ptrPNItem->ptrMNext;
								ptrPUpItem= ptrPNItem;
							}
							return NULL_WJY;
						}
					template<typename Mgr,typename Node>
						Node * __native_Eg_UnRefMapItem(Mgr * ptrMgr,uintV_WJY uIndex,const_WJY char_WJY * ptrKey,intV_WJY iKeySize){
							Node * ptrPUpItem;
							Node * ptrPNItem;
							WJY_ResourceObjectDynamicState eDynamicState;
							intV_WJY iRefCount;
							ptrPNItem = ptrMgr->List[uIndex].ptrRoot;
							ptrPUpItem= ptrMgr->List[uIndex].ptrRoot;
							while(ptrPNItem != NULL_WJY){
								if((iKeySize == ptrPNItem->iNSize) && (WJYSysAPI_MemoryCmp(ptrKey,ptrPNItem->ptrName,iKeySize) == 0)){
									iRefCount = WJYSysAPI_Syn_AtomInterAdd(&(ptrPNItem->iRefCount),-1);
									if(iRefCount<=0){
										eDynamicState = ptrPNItem->eDynamicState;
										if((ptrPNItem != NULL_WJY) && (eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrPNItem->eDynamicState)),
												(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
												(intV_WJY)eDynamicState)==true_WJY)){
											if(ptrPNItem == ptrPUpItem){
												ptrMgr->List[uIndex].ptrRoot = ptrPNItem->ptrMNext;
											}else{
												ptrPUpItem->ptrMNext = ptrPNItem->ptrMNext;
											}
											WJYSysAPI_Syn_AtomInterAdd(&(ptrMgr->iCount),-1);
											return ptrPNItem;
										}
										break;
									}
								}
								ptrPNItem = ptrPNItem->ptrMNext;
								ptrPUpItem= ptrPNItem;
							}
							return NULL_WJY;
						}
					template<typename Mgr,typename Node>
						void_WJY __native_Eg_PushReclaimQueue(Mgr * ptrMgr,Node * ptrItem){
							WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->ReclaimLock));
							ptrItem->ptrMNext = (Node *)(ptrMgr->ptrReclaimQueueRoot);
							ptrMgr->ptrReclaimQueueRoot = ptrItem;
							WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->ReclaimLock));
						}
					template<typename Mgr,typename Node>
						Node * __native_Eg_PopReclaimQueue(Mgr * ptrMgr){
							Node * ptrItem;
							WJYSysAPI_Syn_EnterSpinLock(&(ptrMgr->ReclaimLock));
							ptrItem = (Node *)(ptrMgr->ptrReclaimQueueRoot);
							if(ptrItem!=NULL_WJY){
								ptrMgr->ptrReclaimQueueRoot = ptrItem->ptrMNext;
							}
							WJYSysAPI_Syn_LeaveSpinLock(&(ptrMgr->ReclaimLock));
							return ptrItem;
						}


					template<typename Mgr,typename Node>
						void_WJY __native_Eg_TestReclaim(Mgr * ptrMgr,Node * ptrItem,uintV_WJY uHash){
							Node * ptrRelaseItem;
							WJY_ResourceObjectDynamicState eDynamicState;
							ptrRelaseItem = NULL_WJY;
							eDynamicState = ptrItem->eDynamicState;
							if((eDynamicState != WJYSys_Const_RODynamic_eReclaim) && (WJYSysAPI_JudgeSetValueInt((volatile_WJY intV_WJY *)(&(ptrItem->eDynamicState)),
									(intV_WJY)WJYSys_Const_RODynamic_eReclaim,
									(intV_WJY)eDynamicState)==true_WJY)){
								__native_Eg_RemoveMapItem<WJY_ResourcePolygonManager,WJY_ResourcePolygonItem>(ptrMgr,uHash,ptrItem);
								ptrRelaseItem = ptrItem;
							}
							if(ptrRelaseItem != NULL_WJY){
								__native_Eg_PushReclaimQueue<WJY_ResourcePolygonManager,WJY_ResourcePolygonItem>(ptrMgr,ptrRelaseItem);
							}
						}


/*
					uHash = ptrMgr->hashfunc(ptrItem->ptrName,ptrItem->iNSize,WJYRMgr_ConstID_RPolygonMgrMapSlotMaxSize);

 */

/*
				void_WJY 				 __native_Eg_PushReclaimQueue(WJY_ResourcePolygonManager * ptrMgr,WJY_ResourcePolygonItem * ptrItem);
				WJY_ResourcePolygonItem * __native_Eg_PopReclaimQueue(WJY_ResourcePolygonManager * ptrMgr);
 * */

#endif /* ENGINERESOURCEMANAGERAPI_H_ */
