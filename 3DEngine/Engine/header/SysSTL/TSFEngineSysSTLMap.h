/*
 * TWJYEngineSysSTLMap.h
 *
 *  Created on: 2010-3-5
 *      Author: DevLinux
 */
#include "../TWJYEngineH.h"
#include "../TWJYEngineBaseDataType.h"
#include "../TWJYEngineSysAPI.h"
#include "../TWJYEngineDefine.h"
#include "../TWJYEngineInface.h"
#include "../TWJYEngineMemoryPool.h"
#ifndef TWJYENGINESYSSTLMAP_H_
#define TWJYENGINESYSSTLMAP_H_
	template<typename _WJYstl_Key,typename _WJYstl_Node__>
	struct Aligned(8) __stl_RBMap_CmpFunc {
		inline bool_WJY Priority(_WJYstl_Node__ * & key1,_WJYstl_Node__ * & key2){
			return false_WJY;
		}
	}__Aligned(8);
	template <typename _WJYstl_Key,typename _WJYstl_Node__,typename _stldisposal_func = __stl_RBMap_CmpFunc<_WJYstl_Key , _WJYstl_Node__> >
	class __WJYstl_RBMap_class{
		public:
			__WJYstl_RBMap_class(){

			}
			virtual ~__WJYstl_RBMap_class(){

			}
		protected:

	};
#endif /* TWJYENGINESYSSTLMAP_H_ */
