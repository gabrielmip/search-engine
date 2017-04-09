// This is a generated source file for Chilkat version 9.5.0.56
#ifndef _C_CkImapWH
#define _C_CkImapWH
#include "chilkatDefs.h"

#include "Chilkat_C.h"


CK_VISIBLE_PUBLIC void CkImapW_setAbortCheck(HCkImapW cHandle, BOOL (*fnAbortCheck)());
CK_VISIBLE_PUBLIC void CkImapW_setPercentDone(HCkImapW cHandle, BOOL (*fnPercentDone)(int pctDone));
CK_VISIBLE_PUBLIC void CkImapW_setProgressInfo(HCkImapW cHandle, void (*fnProgressInfo)(const wchar_t *name, const wchar_t *value));
CK_VISIBLE_PUBLIC void CkImapW_setTaskCompleted(HCkImapW cHandle, void (*fnTaskCompleted)(HCkTaskW hTask));

CK_VISIBLE_PUBLIC HCkImapW CkImapW_Create(void);
CK_VISIBLE_PUBLIC HCkImapW CkImapW_Create2(BOOL bCallbackOwned);
CK_VISIBLE_PUBLIC void CkImapW_Dispose(HCkImapW handle);
CK_VISIBLE_PUBLIC BOOL CkImapW_getAppendSeen(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putAppendSeen(HCkImapW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkImapW_getAppendUid(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getAuthMethod(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putAuthMethod(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_authMethod(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getAuthzId(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putAuthzId(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_authzId(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_getAutoDownloadAttachments(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putAutoDownloadAttachments(HCkImapW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC BOOL CkImapW_getAutoFix(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putAutoFix(HCkImapW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkImapW_getClientIpAddress(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putClientIpAddress(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_clientIpAddress(HCkImapW cHandle);
CK_VISIBLE_PUBLIC int CkImapW_getConnectTimeout(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putConnectTimeout(HCkImapW cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkImapW_getConnectedToHost(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_connectedToHost(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getDebugLogFilePath(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putDebugLogFilePath(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_debugLogFilePath(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getDomain(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putDomain(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_domain(HCkImapW cHandle);
CK_VISIBLE_PUBLIC int CkImapW_getHeartbeatMs(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putHeartbeatMs(HCkImapW cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkImapW_getHttpProxyAuthMethod(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putHttpProxyAuthMethod(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_httpProxyAuthMethod(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getHttpProxyDomain(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putHttpProxyDomain(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_httpProxyDomain(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getHttpProxyHostname(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putHttpProxyHostname(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_httpProxyHostname(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getHttpProxyPassword(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putHttpProxyPassword(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_httpProxyPassword(HCkImapW cHandle);
CK_VISIBLE_PUBLIC int CkImapW_getHttpProxyPort(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putHttpProxyPort(HCkImapW cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkImapW_getHttpProxyUsername(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putHttpProxyUsername(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_httpProxyUsername(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_getKeepSessionLog(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putKeepSessionLog(HCkImapW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkImapW_getLastAppendedMime(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_lastAppendedMime(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getLastCommand(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_lastCommand(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getLastErrorHtml(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_lastErrorHtml(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getLastErrorText(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_lastErrorText(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getLastErrorXml(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_lastErrorXml(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getLastIntermediateResponse(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_lastIntermediateResponse(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_getLastMethodSuccess(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putLastMethodSuccess(HCkImapW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkImapW_getLastResponse(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_lastResponse(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getLastResponseCode(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_lastResponseCode(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getLoggedInUser(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_loggedInUser(HCkImapW cHandle);
CK_VISIBLE_PUBLIC int CkImapW_getNumMessages(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_getPeekMode(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putPeekMode(HCkImapW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkImapW_getPercentDoneScale(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putPercentDoneScale(HCkImapW cHandle, int newVal);
CK_VISIBLE_PUBLIC int CkImapW_getPort(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putPort(HCkImapW cHandle, int newVal);
CK_VISIBLE_PUBLIC BOOL CkImapW_getPreferIpv6(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putPreferIpv6(HCkImapW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC int CkImapW_getReadTimeout(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putReadTimeout(HCkImapW cHandle, int newVal);
CK_VISIBLE_PUBLIC BOOL CkImapW_getRequireSslCertVerify(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putRequireSslCertVerify(HCkImapW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkImapW_getSearchCharset(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putSearchCharset(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_searchCharset(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getSelectedMailbox(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_selectedMailbox(HCkImapW cHandle);
CK_VISIBLE_PUBLIC int CkImapW_getSendBufferSize(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putSendBufferSize(HCkImapW cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkImapW_getSeparatorChar(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putSeparatorChar(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_separatorChar(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getSessionLog(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_sessionLog(HCkImapW cHandle);
CK_VISIBLE_PUBLIC int CkImapW_getSoRcvBuf(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putSoRcvBuf(HCkImapW cHandle, int newVal);
CK_VISIBLE_PUBLIC int CkImapW_getSoSndBuf(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putSoSndBuf(HCkImapW cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkImapW_getSocksHostname(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putSocksHostname(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_socksHostname(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getSocksPassword(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putSocksPassword(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_socksPassword(HCkImapW cHandle);
CK_VISIBLE_PUBLIC int CkImapW_getSocksPort(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putSocksPort(HCkImapW cHandle, int newVal);
CK_VISIBLE_PUBLIC void CkImapW_getSocksUsername(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putSocksUsername(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_socksUsername(HCkImapW cHandle);
CK_VISIBLE_PUBLIC int CkImapW_getSocksVersion(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putSocksVersion(HCkImapW cHandle, int newVal);
CK_VISIBLE_PUBLIC BOOL CkImapW_getSsl(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putSsl(HCkImapW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkImapW_getSslAllowedCiphers(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putSslAllowedCiphers(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_sslAllowedCiphers(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getSslProtocol(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putSslProtocol(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_sslProtocol(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_getSslServerCertVerified(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_getStartTls(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putStartTls(HCkImapW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkImapW_getTlsCipherSuite(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_tlsCipherSuite(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getTlsPinSet(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC void CkImapW_putTlsPinSet(HCkImapW cHandle, const wchar_t *newVal);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_tlsPinSet(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_getTlsVersion(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_tlsVersion(HCkImapW cHandle);
CK_VISIBLE_PUBLIC int CkImapW_getUidNext(HCkImapW cHandle);
CK_VISIBLE_PUBLIC int CkImapW_getUidValidity(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_getVerboseLogging(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_putVerboseLogging(HCkImapW cHandle, BOOL newVal);
CK_VISIBLE_PUBLIC void CkImapW_getVersion(HCkImapW cHandle, HCkString retval);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_version(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_AddPfxSourceData(HCkImapW cHandle, HCkByteData pfxBytes, const wchar_t *pfxPassword);
CK_VISIBLE_PUBLIC BOOL CkImapW_AddPfxSourceFile(HCkImapW cHandle, const wchar_t *pfxFilePath, const wchar_t *pfxPassword);
CK_VISIBLE_PUBLIC BOOL CkImapW_AppendMail(HCkImapW cHandle, const wchar_t *mailbox, HCkEmailW email);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_AppendMailAsync(HCkImapW cHandle, const wchar_t *mailbox, HCkEmailW email);
CK_VISIBLE_PUBLIC BOOL CkImapW_AppendMime(HCkImapW cHandle, const wchar_t *mailbox, const wchar_t *mimeText);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_AppendMimeAsync(HCkImapW cHandle, const wchar_t *mailbox, const wchar_t *mimeText);
CK_VISIBLE_PUBLIC BOOL CkImapW_AppendMimeWithDate(HCkImapW cHandle, const wchar_t *mailbox, const wchar_t *mimeText, SYSTEMTIME *internalDate);
CK_VISIBLE_PUBLIC BOOL CkImapW_AppendMimeWithDateStr(HCkImapW cHandle, const wchar_t *mailbox, const wchar_t *mimeText, const wchar_t *internalDateStr);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_AppendMimeWithDateStrAsync(HCkImapW cHandle, const wchar_t *mailbox, const wchar_t *mimeText, const wchar_t *internalDateStr);
CK_VISIBLE_PUBLIC BOOL CkImapW_AppendMimeWithFlags(HCkImapW cHandle, const wchar_t *mailbox, const wchar_t *mimeText, BOOL seen, BOOL flagged, BOOL answered, BOOL draft);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_AppendMimeWithFlagsAsync(HCkImapW cHandle, const wchar_t *mailbox, const wchar_t *mimeText, BOOL seen, BOOL flagged, BOOL answered, BOOL draft);
CK_VISIBLE_PUBLIC BOOL CkImapW_Capability(HCkImapW cHandle, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_capability(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_CapabilityAsync(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_CheckConnection(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkMessageSetW CkImapW_CheckForNewEmail(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_CheckForNewEmailAsync(HCkImapW cHandle);
CK_VISIBLE_PUBLIC void CkImapW_ClearSessionLog(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_CloseMailbox(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_CloseMailboxAsync(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_Connect(HCkImapW cHandle, const wchar_t *domainName);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_ConnectAsync(HCkImapW cHandle, const wchar_t *domainName);
CK_VISIBLE_PUBLIC BOOL CkImapW_Copy(HCkImapW cHandle, int msgId, BOOL bUid, const wchar_t *copyToMailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_CopyAsync(HCkImapW cHandle, int msgId, BOOL bUid, const wchar_t *copyToMailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_CopyMultiple(HCkImapW cHandle, HCkMessageSetW messageSet, const wchar_t *copyToMailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_CopyMultipleAsync(HCkImapW cHandle, HCkMessageSetW messageSet, const wchar_t *copyToMailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_CopySequence(HCkImapW cHandle, int startSeqNum, int count, const wchar_t *copyToMailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_CopySequenceAsync(HCkImapW cHandle, int startSeqNum, int count, const wchar_t *copyToMailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_CreateMailbox(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_CreateMailboxAsync(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_DeleteMailbox(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_DeleteMailboxAsync(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_Disconnect(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_DisconnectAsync(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_ExamineMailbox(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_ExamineMailboxAsync(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_Expunge(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_ExpungeAsync(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_ExpungeAndClose(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_ExpungeAndCloseAsync(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_FetchAttachment(HCkImapW cHandle, HCkEmailW emailObject, int attachmentIndex, const wchar_t *saveToPath);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchAttachmentAsync(HCkImapW cHandle, HCkEmailW emailObject, int attachmentIndex, const wchar_t *saveToPath);
CK_VISIBLE_PUBLIC BOOL CkImapW_FetchAttachmentBytes(HCkImapW cHandle, HCkEmailW email, int attachIndex, HCkByteData outBytes);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchAttachmentBytesAsync(HCkImapW cHandle, HCkEmailW email, int attachIndex);
CK_VISIBLE_PUBLIC BOOL CkImapW_FetchAttachmentString(HCkImapW cHandle, HCkEmailW emailObject, int attachmentIndex, const wchar_t *charset, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_fetchAttachmentString(HCkImapW cHandle, HCkEmailW emailObject, int attachmentIndex, const wchar_t *charset);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchAttachmentStringAsync(HCkImapW cHandle, HCkEmailW emailObject, int attachmentIndex, const wchar_t *charset);
CK_VISIBLE_PUBLIC HCkEmailBundleW CkImapW_FetchBundle(HCkImapW cHandle, HCkMessageSetW messageSet);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchBundleAsync(HCkImapW cHandle, HCkMessageSetW messageSet);
CK_VISIBLE_PUBLIC HCkStringArrayW CkImapW_FetchBundleAsMime(HCkImapW cHandle, HCkMessageSetW messageSet);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchBundleAsMimeAsync(HCkImapW cHandle, HCkMessageSetW messageSet);
CK_VISIBLE_PUBLIC HCkEmailBundleW CkImapW_FetchChunk(HCkImapW cHandle, int startSeqNum, int count, HCkMessageSetW failedSet, HCkMessageSetW fetchedSet);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchChunkAsync(HCkImapW cHandle, int startSeqNum, int count, HCkMessageSetW failedSet, HCkMessageSetW fetchedSet);
CK_VISIBLE_PUBLIC BOOL CkImapW_FetchFlags(HCkImapW cHandle, int msgId, BOOL bUid, HCkString outStrFlags);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_fetchFlags(HCkImapW cHandle, int msgId, BOOL bUid);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchFlagsAsync(HCkImapW cHandle, int msgId, BOOL bUid);
CK_VISIBLE_PUBLIC HCkEmailBundleW CkImapW_FetchHeaders(HCkImapW cHandle, HCkMessageSetW messageSet);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchHeadersAsync(HCkImapW cHandle, HCkMessageSetW messageSet);
CK_VISIBLE_PUBLIC HCkEmailBundleW CkImapW_FetchSequence(HCkImapW cHandle, int startSeqNum, int numMessages);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchSequenceAsync(HCkImapW cHandle, int startSeqNum, int numMessages);
CK_VISIBLE_PUBLIC HCkStringArrayW CkImapW_FetchSequenceAsMime(HCkImapW cHandle, int startSeqNum, int numMessages);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchSequenceAsMimeAsync(HCkImapW cHandle, int startSeqNum, int numMessages);
CK_VISIBLE_PUBLIC HCkEmailBundleW CkImapW_FetchSequenceHeaders(HCkImapW cHandle, int startSeqNum, int numMessages);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchSequenceHeadersAsync(HCkImapW cHandle, int startSeqNum, int numMessages);
CK_VISIBLE_PUBLIC HCkEmailW CkImapW_FetchSingle(HCkImapW cHandle, int msgId, BOOL bUid);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchSingleAsync(HCkImapW cHandle, int msgId, BOOL bUid);
CK_VISIBLE_PUBLIC BOOL CkImapW_FetchSingleAsMime(HCkImapW cHandle, int msgId, BOOL bUid, HCkString outStrMime);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_fetchSingleAsMime(HCkImapW cHandle, int msgId, BOOL bUid);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchSingleAsMimeAsync(HCkImapW cHandle, int msgId, BOOL bUid);
CK_VISIBLE_PUBLIC HCkEmailW CkImapW_FetchSingleHeader(HCkImapW cHandle, int msgId, BOOL bUid);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchSingleHeaderAsync(HCkImapW cHandle, int msgId, BOOL bUid);
CK_VISIBLE_PUBLIC BOOL CkImapW_FetchSingleHeaderAsMime(HCkImapW cHandle, int msgId, BOOL bUID, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_fetchSingleHeaderAsMime(HCkImapW cHandle, int msgId, BOOL bUID);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_FetchSingleHeaderAsMimeAsync(HCkImapW cHandle, int msgId, BOOL bUID);
CK_VISIBLE_PUBLIC HCkMessageSetW CkImapW_GetAllUids(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_GetAllUidsAsync(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_GetMailAttachFilename(HCkImapW cHandle, HCkEmailW email, int attachIndex, HCkString outStrFilename);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_getMailAttachFilename(HCkImapW cHandle, HCkEmailW email, int attachIndex);
CK_VISIBLE_PUBLIC int CkImapW_GetMailAttachSize(HCkImapW cHandle, HCkEmailW email, int attachIndex);
CK_VISIBLE_PUBLIC int CkImapW_GetMailFlag(HCkImapW cHandle, HCkEmailW email, const wchar_t *flagName);
CK_VISIBLE_PUBLIC int CkImapW_GetMailNumAttach(HCkImapW cHandle, HCkEmailW email);
CK_VISIBLE_PUBLIC int CkImapW_GetMailSize(HCkImapW cHandle, HCkEmailW email);
CK_VISIBLE_PUBLIC BOOL CkImapW_GetMailboxStatus(HCkImapW cHandle, const wchar_t *mailbox, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_getMailboxStatus(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_GetMailboxStatusAsync(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC HCkCertW CkImapW_GetSslServerCert(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_IdleCheck(HCkImapW cHandle, int timeoutMs, HCkString outStr);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_idleCheck(HCkImapW cHandle, int timeoutMs);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_IdleCheckAsync(HCkImapW cHandle, int timeoutMs);
CK_VISIBLE_PUBLIC BOOL CkImapW_IdleDone(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_IdleDoneAsync(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_IdleStart(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_IdleStartAsync(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_IsConnected(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_IsLoggedIn(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_IsUnlocked(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkMailboxesW CkImapW_ListMailboxes(HCkImapW cHandle, const wchar_t *reference, const wchar_t *wildcardedMailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_ListMailboxesAsync(HCkImapW cHandle, const wchar_t *reference, const wchar_t *wildcardedMailbox);
CK_VISIBLE_PUBLIC HCkMailboxesW CkImapW_ListSubscribed(HCkImapW cHandle, const wchar_t *reference, const wchar_t *wildcardedMailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_ListSubscribedAsync(HCkImapW cHandle, const wchar_t *reference, const wchar_t *wildcardedMailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_Login(HCkImapW cHandle, const wchar_t *login, const wchar_t *password);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_LoginAsync(HCkImapW cHandle, const wchar_t *login, const wchar_t *password);
CK_VISIBLE_PUBLIC BOOL CkImapW_Logout(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_LogoutAsync(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_Noop(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_NoopAsync(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_RefetchMailFlags(HCkImapW cHandle, HCkEmailW email);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_RefetchMailFlagsAsync(HCkImapW cHandle, HCkEmailW email);
CK_VISIBLE_PUBLIC BOOL CkImapW_RenameMailbox(HCkImapW cHandle, const wchar_t *fromMailbox, const wchar_t *toMailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_RenameMailboxAsync(HCkImapW cHandle, const wchar_t *fromMailbox, const wchar_t *toMailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_SaveLastError(HCkImapW cHandle, const wchar_t *path);
CK_VISIBLE_PUBLIC HCkMessageSetW CkImapW_Search(HCkImapW cHandle, const wchar_t *criteria, BOOL bUid);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SearchAsync(HCkImapW cHandle, const wchar_t *criteria, BOOL bUid);
CK_VISIBLE_PUBLIC BOOL CkImapW_SelectMailbox(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SelectMailboxAsync(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_SendRawCommand(HCkImapW cHandle, const wchar_t *cmd, HCkString outRawResponse);
CK_VISIBLE_PUBLIC const wchar_t *CkImapW_sendRawCommand(HCkImapW cHandle, const wchar_t *cmd);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SendRawCommandAsync(HCkImapW cHandle, const wchar_t *cmd);
CK_VISIBLE_PUBLIC BOOL CkImapW_SendRawCommandB(HCkImapW cHandle, const wchar_t *cmd, HCkByteData outBytes);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SendRawCommandBAsync(HCkImapW cHandle, const wchar_t *cmd);
CK_VISIBLE_PUBLIC BOOL CkImapW_SendRawCommandC(HCkImapW cHandle, HCkByteData cmd, HCkByteData outBytes);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SendRawCommandCAsync(HCkImapW cHandle, HCkByteData cmd);
#if defined(CK_CSP_INCLUDED)
CK_VISIBLE_PUBLIC BOOL CkImapW_SetCSP(HCkImapW cHandle, HCkCspW csp);
#endif
CK_VISIBLE_PUBLIC BOOL CkImapW_SetDecryptCert(HCkImapW cHandle, HCkCertW cert);
CK_VISIBLE_PUBLIC BOOL CkImapW_SetDecryptCert2(HCkImapW cHandle, HCkCertW cert, HCkPrivateKeyW key);
CK_VISIBLE_PUBLIC BOOL CkImapW_SetFlag(HCkImapW cHandle, int msgId, BOOL bUid, const wchar_t *flagName, int value);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SetFlagAsync(HCkImapW cHandle, int msgId, BOOL bUid, const wchar_t *flagName, int value);
CK_VISIBLE_PUBLIC BOOL CkImapW_SetFlags(HCkImapW cHandle, HCkMessageSetW messageSet, const wchar_t *flagName, int value);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SetFlagsAsync(HCkImapW cHandle, HCkMessageSetW messageSet, const wchar_t *flagName, int value);
CK_VISIBLE_PUBLIC BOOL CkImapW_SetMailFlag(HCkImapW cHandle, HCkEmailW email, const wchar_t *flagName, int value);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SetMailFlagAsync(HCkImapW cHandle, HCkEmailW email, const wchar_t *flagName, int value);
CK_VISIBLE_PUBLIC BOOL CkImapW_SetSslClientCert(HCkImapW cHandle, HCkCertW cert);
CK_VISIBLE_PUBLIC BOOL CkImapW_SetSslClientCertPem(HCkImapW cHandle, const wchar_t *pemDataOrFilename, const wchar_t *pemPassword);
CK_VISIBLE_PUBLIC BOOL CkImapW_SetSslClientCertPfx(HCkImapW cHandle, const wchar_t *pfxFilename, const wchar_t *pfxPassword);
CK_VISIBLE_PUBLIC BOOL CkImapW_SshAuthenticatePk(HCkImapW cHandle, const wchar_t *sshLogin, HCkSshKeyW privateKey);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SshAuthenticatePkAsync(HCkImapW cHandle, const wchar_t *sshLogin, HCkSshKeyW privateKey);
CK_VISIBLE_PUBLIC BOOL CkImapW_SshAuthenticatePw(HCkImapW cHandle, const wchar_t *sshLogin, const wchar_t *sshPassword);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SshAuthenticatePwAsync(HCkImapW cHandle, const wchar_t *sshLogin, const wchar_t *sshPassword);
CK_VISIBLE_PUBLIC BOOL CkImapW_SshCloseTunnel(HCkImapW cHandle);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SshCloseTunnelAsync(HCkImapW cHandle);
CK_VISIBLE_PUBLIC BOOL CkImapW_SshOpenTunnel(HCkImapW cHandle, const wchar_t *sshHostname, int sshPort);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SshOpenTunnelAsync(HCkImapW cHandle, const wchar_t *sshHostname, int sshPort);
CK_VISIBLE_PUBLIC BOOL CkImapW_StoreFlags(HCkImapW cHandle, int msgId, BOOL bUid, const wchar_t *flagNames, int value);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_StoreFlagsAsync(HCkImapW cHandle, int msgId, BOOL bUid, const wchar_t *flagNames, int value);
CK_VISIBLE_PUBLIC BOOL CkImapW_Subscribe(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_SubscribeAsync(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_UnlockComponent(HCkImapW cHandle, const wchar_t *unlockCode);
CK_VISIBLE_PUBLIC BOOL CkImapW_Unsubscribe(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC HCkTaskW CkImapW_UnsubscribeAsync(HCkImapW cHandle, const wchar_t *mailbox);
CK_VISIBLE_PUBLIC BOOL CkImapW_UseCertVault(HCkImapW cHandle, HCkXmlCertVaultW vault);
CK_VISIBLE_PUBLIC BOOL CkImapW_UseSsh(HCkImapW cHandle, HCkSshW ssh);
CK_VISIBLE_PUBLIC BOOL CkImapW_UseSshTunnel(HCkImapW cHandle, HCkSocketW tunnel);
#endif
