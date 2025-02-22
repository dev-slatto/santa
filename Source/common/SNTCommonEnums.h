/// Copyright 2015-2022 Google Inc. All rights reserved.
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///    http://www.apache.org/licenses/LICENSE-2.0
///
///    Unless required by applicable law or agreed to in writing, software
///    distributed under the License is distributed on an "AS IS" BASIS,
///    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
///    See the License for the specific language governing permissions and
///    limitations under the License.

#import <Foundation/Foundation.h>

///
///  These enums are used in various places throughout the Santa client code.
///  The integer values are also stored in the database and so shouldn't be changed.
///

typedef NS_ENUM(NSInteger, SNTAction) {
  SNTActionUnset,

  // REQUESTS
  // If an operation is awaiting a cache decision from a similar operation
  // currently being processed, it will poll about every 5 ms for an answer.
  SNTActionRequestBinary,

  // RESPONSES
  SNTActionRespondAllow,
  SNTActionRespondDeny,
  SNTActionRespondAllowCompiler,
};

#define RESPONSE_VALID(x) \
  (x == SNTActionRespondAllow || x == SNTActionRespondDeny || x == SNTActionRespondAllowCompiler)

typedef NS_ENUM(NSInteger, SNTRuleType) {
  SNTRuleTypeUnknown,

  SNTRuleTypeBinary = 1,
  SNTRuleTypeCertificate = 2,
  SNTRuleTypeTeamID = 3,
};

typedef NS_ENUM(NSInteger, SNTRuleState) {
  SNTRuleStateUnknown,

  SNTRuleStateAllow = 1,
  SNTRuleStateBlock = 2,
  SNTRuleStateSilentBlock = 3,
  SNTRuleStateRemove = 4,

  SNTRuleStateAllowCompiler = 5,
  SNTRuleStateAllowTransitive = 6,
};

typedef NS_ENUM(NSInteger, SNTClientMode) {
  SNTClientModeUnknown,

  SNTClientModeMonitor = 1,
  SNTClientModeLockdown = 2,
};

typedef NS_ENUM(NSInteger, SNTEventState) {
  // Bits 0-15 bits store non-decision types
  SNTEventStateUnknown = 0,
  SNTEventStateBundleBinary = 1,

  // Bits 16-23 store deny decision types
  SNTEventStateBlockUnknown = 1 << 16,
  SNTEventStateBlockBinary = 1 << 17,
  SNTEventStateBlockCertificate = 1 << 18,
  SNTEventStateBlockScope = 1 << 19,
  SNTEventStateBlockTeamID = 1 << 20,
  SNTEventStateBlockLongPath = 1 << 21,

  // Bits 24-31 store allow decision types
  SNTEventStateAllowUnknown = 1 << 24,
  SNTEventStateAllowBinary = 1 << 25,
  SNTEventStateAllowCertificate = 1 << 26,
  SNTEventStateAllowScope = 1 << 27,
  SNTEventStateAllowCompiler = 1 << 28,
  SNTEventStateAllowTransitive = 1 << 29,
  SNTEventStateAllowPendingTransitive = 1 << 30,
  SNTEventStateAllowTeamID = 1 << 31,

  // Block and Allow masks
  SNTEventStateBlock = 0xFF << 16,
  SNTEventStateAllow = 0xFF << 24
};

typedef NS_ENUM(NSInteger, SNTRuleTableError) {
  SNTRuleTableErrorEmptyRuleArray,
  SNTRuleTableErrorInsertOrReplaceFailed,
  SNTRuleTableErrorInvalidRule,
  SNTRuleTableErrorRemoveFailed
};

// This enum type is used to indicate what should be done with the related bundle events that are
// generated when an initiating blocked bundle event occurs.
typedef NS_ENUM(NSInteger, SNTBundleEventAction) {
  SNTBundleEventActionDropEvents,
  SNTBundleEventActionStoreEvents,
  SNTBundleEventActionSendEvents,
};

// Indicates where to store event logs.
typedef NS_ENUM(NSInteger, SNTEventLogType) {
  SNTEventLogTypeSyslog,
  SNTEventLogTypeFilelog,
  SNTEventLogTypeProtobuf,
  SNTEventLogTypeNull,
};

// The return status of a sync.
typedef NS_ENUM(NSInteger, SNTSyncStatusType) {
  SNTSyncStatusTypeSuccess,
  SNTSyncStatusTypePreflightFailed,
  SNTSyncStatusTypeEventUploadFailed,
  SNTSyncStatusTypeRuleDownloadFailed,
  SNTSyncStatusTypePostflightFailed,
  SNTSyncStatusTypeTooManySyncsInProgress,
  SNTSyncStatusTypeMissingSyncBaseURL,
  SNTSyncStatusTypeMissingMachineID,
  SNTSyncStatusTypeDaemonTimeout,
  SNTSyncStatusTypeSyncStarted,
  SNTSyncStatusTypeUnknown,
};

typedef NS_ENUM(NSInteger, SNTMetricFormatType) {
  SNTMetricFormatTypeUnknown,
  SNTMetricFormatTypeRawJSON,
  SNTMetricFormatTypeMonarchJSON,
};

#ifdef __cplusplus
enum class FileAccessPolicyDecision {
  kNoPolicy,
  kDenied,
  kDeniedInvalidSignature,
  kAllowed,
  kAllowedReadAccess,
  kAllowedAuditOnly,
};
#endif

static const char *kSantaDPath =
  "/Applications/Santa.app/Contents/Library/SystemExtensions/"
  "com.google.santa.daemon.systemextension/Contents/MacOS/com.google.santa.daemon";
static const char *kSantaAppPath = "/Applications/Santa.app";
