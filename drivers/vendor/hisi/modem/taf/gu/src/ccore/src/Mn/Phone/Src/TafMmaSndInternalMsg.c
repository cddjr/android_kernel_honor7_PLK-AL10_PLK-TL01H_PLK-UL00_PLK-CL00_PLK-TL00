
/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafLog.h"
#include "TafMmaCtx.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_SND_INTERNAL_MSG_C

/*****************************************************************************
  2 全局变量
*****************************************************************************/

/*****************************************************************************
  3 宏定义
*****************************************************************************/


/*****************************************************************************
  4 函数实现
*****************************************************************************/

TAF_MMA_INTERNAL_MSG_BUF_STRU* TAF_MMA_GetNextInternalMsg( VOS_VOID )
{
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstNextMsg = VOS_NULL_PTR;
    TAF_MMA_CONTEXT_STRU               *pstMmaCtx  =  VOS_NULL_PTR;
    VOS_UINT8                           ucNextIndex;

    pstMmaCtx   = TAF_MMA_GetMmaCtxAddr();

    if (pstMmaCtx->stInternalMsgQueue.ucHeader != pstMmaCtx->stInternalMsgQueue.ucTail)
    {
        ucNextIndex     = pstMmaCtx->stInternalMsgQueue.ucHeader;
        pstNextMsg      = (TAF_MMA_INTERNAL_MSG_BUF_STRU *)&(pstMmaCtx->stInternalMsgQueue.astMmaMsgQueue[ucNextIndex]);

        /* 取完一条消息,头指针向后偏移 */
        (pstMmaCtx->stInternalMsgQueue.ucHeader)++;
        (pstMmaCtx->stInternalMsgQueue.ucHeader) %= TAF_MMA_MAX_MSG_QUEUE_SIZE;

        return pstNextMsg;
    }

    TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_GetNextInternalMsg:Empty Internal Msg");

    return VOS_NULL_PTR;

}
TAF_MMA_INTERNAL_MSG_BUF_STRU *TAF_MMA_GetIntMsgSendBuf(
    VOS_UINT32                          ulLen
)
{
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstTafMmaMsg        = VOS_NULL_PTR;
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;

    pstInternalMsgQueue         = &(TAF_MMA_GetMmaCtxAddr()->stInternalMsgQueue);

    /* 从上下文中获取消息缓冲区指针 */
    pstTafMmaMsg = ( TAF_MMA_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->stSendMsgBuf);

    if (ulLen > TAF_MMA_MAX_MSG_BUFFER_LEN )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_GetIntMsgSendBuf: Buffer full" );

        TAF_MMA_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_FALSE);

        return VOS_NULL_PTR;
    }

    /* 清空这个消息缓冲单元 */
    PS_MEM_SET(pstTafMmaMsg, 0x00, sizeof(TAF_MMA_INTERNAL_MSG_BUF_STRU));

    /* 返回缓冲区指针 */
    return pstTafMmaMsg;
}
VOS_UINT32  TAF_MMA_SndInternalMsg(
    VOS_VOID                           *pSndMsg
)
{
    VOS_UINT8                           ucMsgPnt;
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstMmaMsg           = VOS_NULL_PTR;
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstSndMsg           = VOS_NULL_PTR;

    pstInternalMsgQueue                 = &(TAF_MMA_GetMmaCtxAddr()->stInternalMsgQueue);
    pstSndMsg                           = (TAF_MMA_INTERNAL_MSG_BUF_STRU*)pSndMsg;

    /* 1. 判断内部消息缓冲区是否已满 */
    ucMsgPnt = pstInternalMsgQueue->ucTail;
    if ( ((ucMsgPnt + 1) % TAF_MMA_MAX_MSG_QUEUE_SIZE) == pstInternalMsgQueue->ucHeader )
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_SndInternalMsg:Warning: The Queue is full.");
        TAF_MMA_SndOmInternalMsgQueueInfo(VOS_TRUE, VOS_FALSE);
        return VOS_FALSE;
    }

    /* 2. 取得一个消息缓冲单元 */
    pstMmaMsg = (TAF_MMA_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->astMmaMsgQueue[ucMsgPnt]);

    /* 3. 判断消息长度是否非法 */
    if ( pstSndMsg->ulLength > TAF_MMA_MAX_MSG_BUFFER_LEN)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMC, "TAF_MMA_SndInternalMsg:Warning: ulBufLen is too long.");
        return VOS_FALSE;
    }

    TAF_NORMAL_LOG1(WUEPS_PID_MMA, "TAF_MMA_SndInternalMsg: usMsgID is ", pstMmaMsg->usMsgID);

    /* 4. 将内部消息发送到内部消息队列中 */
    PS_MEM_CPY(pstMmaMsg, pstSndMsg, sizeof(TAF_MMA_INTERNAL_MSG_BUF_STRU));

    /* 更新内部消息缓冲区 */
    pstInternalMsgQueue->ucTail++;
    pstInternalMsgQueue->ucTail         %= TAF_MMA_MAX_MSG_QUEUE_SIZE;

    return VOS_TRUE;
}
VOS_VOID TAF_MMA_SndInterPowerInitReq(VOS_VOID)
{
    TAF_MMA_INTER_POWER_INIT_REQ_STRU  *pstPowerInitMsg = VOS_NULL_PTR;

    pstPowerInitMsg  = (TAF_MMA_INTER_POWER_INIT_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                       sizeof(TAF_MMA_INTER_POWER_INIT_REQ_STRU));

    if (VOS_NULL_PTR == pstPowerInitMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,
                      "TAF_MMA_SndMmaPowerInitReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPowerInitMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(TAF_MMA_INTER_POWER_INIT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPowerInitMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstPowerInitMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstPowerInitMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstPowerInitMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstPowerInitMsg->MsgHeader.ulMsgName       = MMA_MMA_INTER_POWER_INIT;
    pstPowerInitMsg->MsgHeader.ulLength        = sizeof(TAF_MMA_INTER_POWER_INIT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 需要发送外部消息,因为上电时无外部消息触发内部消息 */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstPowerInitMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,
                      "TAF_MMA_SndMmaPowerInitReq: Send message failed.");
    }

    return;
}
VOS_VOID TAF_MMA_SndInterUsimChangeInd(VOS_VOID)
{
    TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU              *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU);

    pstInternalMsg  = (TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulMsgName       = MMA_MMA_INTER_USIM_STATUS_CHANGE_IND;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}
VOS_VOID TAF_MMA_SndSimlocakStatusChangeInd(VOS_VOID)
{
    TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU                *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU);

    pstInternalMsg  = (TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulMsgName       = MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}
VOS_VOID TAF_MMA_SndPhoneModeRsltInd(
    TAF_MMA_PHONE_MODE_RESULT_ENUM_UINT8                    enRslt
)
{
    TAF_MMA_PHONE_MODE_RSLT_IND_STRU   *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* 从内部消息队列中获取一个还没有使用的空间 */
    ulLen           = sizeof(TAF_MMA_PHONE_MODE_RSLT_IND_STRU);

    pstInternalMsg  = (TAF_MMA_PHONE_MODE_RSLT_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              ulLen - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulMsgName       = MMA_MMA_PHONE_MODE_RSLT_IND;
    pstInternalMsg->MsgHeader.ulLength        = ulLen - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enRslt                    = enRslt;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



