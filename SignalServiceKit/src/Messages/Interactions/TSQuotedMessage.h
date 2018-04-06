//
//  Copyright (c) 2018 Open Whisper Systems. All rights reserved.
//

#import <Mantle/MTLModel.h>
#import <SignalServiceKit/TSYapDatabaseObject.h>

NS_ASSUME_NONNULL_BEGIN

@class TSAttachment;
@class TSAttachmentStream;
@class TSQuotedMessage;

@interface OWSQuotedReplyDraft : NSObject

@property (nonatomic, readonly) uint64_t timestamp;
@property (nonatomic, readonly) NSString *authorId;
@property (nonatomic, readonly, nullable) TSAttachmentStream *attachmentStream;

// This property should be set IFF we are quoting a text message
// or attachment with caption.
@property (nullable, nonatomic, readonly) NSString *body;

#pragma mark - Attachments

// This is a MIME type.
//
// This property should be set IFF we are quoting an attachment message.
@property (nonatomic, readonly, nullable) NSString *contentType;
@property (nonatomic, readonly, nullable) NSString *sourceFilename;
@property (nonatomic, readonly, nullable) UIImage *thumbnailImage;

- (instancetype)initWithTimestamp:(uint64_t)timestamp
                         authorId:(NSString *)authorId
                             body:(NSString *_Nullable)body
                 attachmentStream:(nullable TSAttachmentStream *)attachment;

- (TSQuotedMessage *)buildQuotedMessage;

@end

@interface OWSAttachmentInfo: MTLModel

@property (nonatomic, readonly, nullable) NSString *contentType;
@property (nonatomic, readonly, nullable) NSString *sourceFilename;
@property (nonatomic, readonly, nullable) NSString *attachmentId;

- (instancetype)init NS_UNAVAILABLE;

- (instancetype)initWithAttachmentId:(nullable NSString *)attachmentId
                         contentType:(NSString *)contentType
                      sourceFilename:(NSString *)sourceFilename NS_DESIGNATED_INITIALIZER;

- (instancetype)initWithAttachment:(TSAttachment *)attachment;

@end

@interface TSQuotedMessage : TSYapDatabaseObject

@property (nonatomic, readonly) uint64_t timestamp;
@property (nonatomic, readonly) NSString *authorId;

// This property should be set IFF we are quoting a text message
// or attachment with caption.
@property (nullable, nonatomic, readonly) NSString *body;

#pragma mark - Attachments

// This is a MIME type.
//
// This property should be set IFF we are quoting an attachment message.
- (nullable NSString *)contentType;
- (nullable NSString *)sourceFilename;

@property (atomic, readonly) NSArray<OWSAttachmentInfo *> *quotedAttachments;
//- (void)addAttachment:(TSAttachmentStream *)attachment;
- (BOOL)hasAttachments;

- (nullable TSAttachment *)firstAttachmentWithTransaction:(YapDatabaseReadTransaction *)transaction;
- (nullable UIImage *)thumbnailImageWithTransaction:(YapDatabaseReadTransaction *)transaction;

- (instancetype)init NS_UNAVAILABLE;

// used in message manager
- (instancetype)initWithTimestamp:(uint64_t)timestamp
                         authorId:(NSString *)authorId
                             body:(NSString *_Nullable)body
            quotedAttachmentInfos:(NSArray<OWSAttachmentInfo *> *)attachmentInfos;

// used by OWSAttachmentInfo#buildQuotedMessage
- (instancetype)initWithTimestamp:(uint64_t)timestamp
                         authorId:(NSString *)authorId
                             body:(NSString *_Nullable)body
      quotedAttachmentsForSending:(NSArray<TSAttachment *> *)attachments;


@end

#pragma mark -

NS_ASSUME_NONNULL_END
