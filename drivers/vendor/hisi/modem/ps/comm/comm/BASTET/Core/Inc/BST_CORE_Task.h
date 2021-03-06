

#ifndef __BST_CORE_TASK_H__
#define __BST_CORE_TASK_H__
/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "BST_Platform.h"

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack(4)
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define BST_IsTaskTypeValid( enType )   ( ( (enType)<BST_TASK_TYPE_BUTT )\
                                        &&( (enType)>BST_TASK_TYPE_INVALID ) )

#define BST_GetTaskTypeInId( TaskId )   ( (BST_TASK_TYPE_ENUM_UINT8)( ( (TaskId) >>16) & 0xffff ) )

#define BST_IsRunModeValid( RunMode )   ( (RunMode) < BST_TASK_RUN_BUTT )

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 枚举定义
*****************************************************************************/
enum BST_TASK_TYPE_ENUM{
    BST_TASK_TYPE_INVALID               = 0,
    BST_TASK_TYPE_MAIN,
    BST_TASK_TYPE_MBOX,
    BST_TASK_TYPE_CYCL,
    BST_TASK_TYPE_SIGL,
    BST_TASK_TYPE_BUTT
};
typedef BST_UINT8                       BST_TASK_TYPE_ENUM_UINT8;

enum BST_TASK_RUN_MODE_ENUM{
    BST_TASK_RUN_UNBLOCKED,
    BST_TASK_RUN_BLOCKED,
    BST_TASK_RUN_BUTT
};
typedef BST_UINT8                       BST_RUN_MODE_ENUM_UINT8;

enum BST_TASK_STATE_ENUM{
    BST_TASK_STATE_STOPED,
    BST_TASK_STATE_START,
    BST_TASK_STATE_SUSPEND
};
typedef BST_UINT8                       BST_TASK_STATE_ENUM_UINT8;


/*****************************************************************************
  5 类/结构定义
*****************************************************************************/
class BST_SRV_CTaskMng;

class BST_CTask
{
BST_PUBLIC:
    virtual BST_VOID                    Entry       ( BST_VOID )
    { return; }

    virtual BST_VOID                    Start       ( BST_VOID );
    virtual BST_VOID                    Stop        ( BST_VOID );
    BST_TASK_STATE_ENUM_UINT8           GetState    ( BST_VOID );
    BST_RUN_MODE_ENUM_UINT8             GetRunMode  ( BST_VOID );
    BST_VOID                            SetRunMode  ( BST_RUN_MODE_ENUM_UINT8 enRunMode );
    const BST_PROCID_T                  m_usProcId;
    const BST_TASKID_T                  m_usTaskId;
    friend class                        BST_SRV_CTaskMng;
BST_PROTECTED:
                                        BST_CTask   ( BST_PROCID_T in_usProcId, BST_TASKID_T in_usTaskId );
    virtual                            ~BST_CTask   ( BST_VOID );
    BST_TASK_STATE_ENUM_UINT8           m_enState;               /*relate to Start/Stop Action*/
    BST_RUN_MODE_ENUM_UINT8             m_enRunMode;
};

/*****************************************************************************
  6 UNION定义
*****************************************************************************/


/*****************************************************************************
  7 全局变量声明
*****************************************************************************/


/*****************************************************************************
  8 函数声明
*****************************************************************************/

/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/

#if (BST_OS_VER == BST_HISI_VOS)
#pragma pack()
#elif(BST_OS_VER == BST_WIN32)
#pragma pack(pop)
#endif


#endif
