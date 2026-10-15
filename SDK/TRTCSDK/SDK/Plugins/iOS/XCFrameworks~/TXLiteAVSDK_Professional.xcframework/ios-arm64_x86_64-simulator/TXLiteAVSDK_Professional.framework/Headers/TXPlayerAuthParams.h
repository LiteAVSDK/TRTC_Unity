//  Copyright © 2021 Tencent. All rights reserved.

#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"
#import "TXVodPlayConfig.h"

/**
 * The configuration for encrypted video playback through fileId.
 */
LITEAV_EXPORT @interface TXPlayerAuthParams : NSObject

/// The application's appId, which is required.
@property(nonatomic, assign) int appId;

/// The file ID, which is required.
@property(nonatomic, copy) NSString *fileId;

/// The encrypted link timeout timestamp, which is optional and will be converted to a hexadecimal lowercase string. The CDN server will determine whether the link is valid based on the timestamp.
@property(nonatomic, copy) NSString *timeout;

/// The preview duration in seconds, which is optional.
@property(nonatomic, assign) int exper;

/// The unique request ID, which increases the link uniqueness.
@property(nonatomic, copy) NSString *us;

/// If hotlink protection is not used, leave this parameter empty.
/// General hotlink protection signature:
/// sign = md5(KEY+appId+fileId+t+us)sign = md5(KEY+appId+fileId+t+us)
/// Preview-enabled hotlink protection signature:
/// sign = md5(KEY+appId+fileId+t+exper+us)
/// The hotlink protection parameters (t, us, and exper) used by the player APIs are the same as those in CDN, and the only difference is the calculation method of sign.
/// For more information, visit https://www.tencentcloud.com/document/product/266/33984?lang=en&pg=.
@property(nonatomic, copy) NSString *sign;

/// This API is used to set whether to use HTTPS requests, which is no by default.
@property(nonatomic, assign) BOOL https;

/// url is required if fileId is not provided.
@property(nonatomic, copy) NSString *url;

/// This API is used to set media type, which is `MEDIA_TYPE_AUTO` by default.
@property(nonatomic, assign) TX_Enum_MediaType mediaType;

/// Sets the encryption level for MP4 playback, corresponding to TXVodPlayConfig.encryptedMp4Level.
/// MP4_ENCRYPTION_LEVEL_NONE: Playback without encryption.
/// MP4_ENCRYPTION_LEVEL_L1: Online encryption.
/// MP4_ENCRYPTION_LEVEL_L2: Local encryption.
@property(nonatomic, assign) TX_Enum_MP4EncryptionLevel encryptedMp4Level;

/// Set the httpHeader
@property(nonatomic, strong) NSDictionary *headers;

/// Set the preloading preferred audio track name
@property(nonatomic, copy) NSString *preferAudioTrack;

@end
