/**
 * Copyright (c) 2025 Tencent. All rights reserved.
 * Module: management class for AI real-time transcription and translation
 * Function: management class for setting AI real-time transcription and translation functions
 */
#import <Foundation/Foundation.h>
#import "TXLiteAVSymbolExport.h"
NS_ASSUME_NONNULL_BEGIN

/**
 * Configuration parameters for real-time transcription.
 *
 * Structure used to specify parameters when calling the {@link startRealtimeTranscriber} interface, such as the transcriber robot ID, source language, list of users to transcribe, and target translation languages.
 */
LITEAV_EXPORT @interface TranscriberParams : NSObject

/// Field description: Unique ID of the transcriber robot.
/// @note If this field is not specified, the SDK will automatically generate an ID in the format "transcriber_${roomid}_robot_${userid}".
@property(nonatomic, copy) NSString *transcriberRobotId;

/// Field description: Source language code.
/// @note Specifies the language of the source audio. Please provide standard language codes (e.g., "zh"), not language names.
///@note Currently supports 2 languages: "zh" (Chinese) and "en" (English). Contact us if you need support for other languages.
@property(nonatomic, copy) NSString *sourceLanguage;

/// Field description: List of user IDs to transcribe.
/// @note Specifies which users' audio to transcribe. If not specified, all users in the room will be transcribed by default.
@property(nonatomic, copy) NSArray<NSString *> *userIdsToTranscribe;

/// Field description: List of target language codes for translation.
/// @note If you need to translate the transcription results into other languages, set the target language codes here. Supported languages include:
/// "zh"(Chinese), "en"(English), "vi"(Vietnamese), "ja"(Japanese), "ko"(Korean), "id"(Indonesian), "th"(Thai), "pt"(Portuguese),
/// "ar"(Arabic), "es"(Spanish), "fr"(French), "ms"(Malay), "de"(German), "it"(Italian), "ru"(Russian).
@property(nonatomic, copy) NSArray<NSString *> *translationLanguages;

@end

/**
 * Structure for real-time transcription messages.
 *
 * The SDK uses this structure to callback the transcribed text and translation results to you.
 */
LITEAV_EXPORT @interface TranscriberMessage : NSObject

/// Field description: Unique ID of the message segment.
/// @note Unique ID used to identify the message segment.
@property(nonatomic, copy) NSString *segmentId;

/// Field description: Speaker's user ID.
/// @note User ID of the speaker.
@property(nonatomic, copy) NSString *speakerUserId;

/// Field description: Recognized source language text.
/// @note This text is Unicode encoded.
@property(nonatomic, copy) NSString *sourceText;

/// Field description: List of translated texts in target languages.
/// @note Key is the translation language code (e.g., "zh", "en"), and value is the translated text. For C++, this is an array of TranslationText structures.
@property(nonatomic, copy) NSDictionary *translationTexts;

/// Field description: Message generation timestamp in UTC, unit: milliseconds.
/// @note Timestamp when the message was generated, in milliseconds (UTC).
@property(nonatomic, assign) int64_t timestamp;

/// Field description: Whether transcription is completed.
/// @note True indicates that the sentence is complete; false indicates that the sentence is still in progress (intermediate result).
@property(nonatomic, assign) BOOL isCompleted;

@end

/**
 * Event callback interface for AI real-time transcription.
 */
@protocol AITranscriberListener <NSObject>
@optional

/**
 * Real-time transcription started callback.
 *
 * Received when the transcription task is successfully started after calling startRealtimeTranscriber.
 * @param roomId Room ID
 * @param transcriberRobotId Transcriber robot ID
 */
- (void)onRealtimeTranscriberStarted:(NSString *)roomId transcriberRobotId:(NSString *)transcriberRobotId;

/**
 * Receive transcription message callback.
 *
 * The transcription service pushes the recognized text and translation results to you in real-time through this callback.
 * @param roomId Room ID
 * @param message Transcription message. For details, please refer to {@link TranscriberMessage}.
 */
- (void)onReceiveTranscriberMessage:(NSString *)roomId message:(TranscriberMessage *)message;

/**
 * Real-time transcription stopped callback.
 *
 * Received when the real-time transcription task is stopped.
 * @param roomId Room ID
 * @param transcriberRobotId Transcriber robot ID
 * @param reason Reason.
 * - 0: User proactively stopped the transcription task.
 * - 1: Room was dissolved by the server.
 * - 2: All users involved in transcription left the room for more than 30 seconds, causing the task to end automatically.
 */
- (void)onRealtimeTranscriberStopped:(NSString *)roomId transcriberRobotId:(NSString *)transcriberRobotId reason:(NSInteger)reason;

/**
 * Real-time transcription error callback.
 *
 * Received when an error occurs in the real-time transcription service.
 * @param roomId Room ID
 * @param transcriberRobotId Transcriber robot ID
 * @param error Error code
 * @param errorInfo Error information
 * If the error code is ERR_SERVER_PROCESS_FAILED, it indicates a server-side processing failure. Specific error codes and recommended actions are as follows:
 * - 2000: Parameter error. Please check if the parameters are valid.
 * - 2002: Task does not exist. This can be ignored if returned when calling the stop interface.
 * - 2026: Transcription service (ASR/Translation) is not enabled. Please enable the service in the console.
 * - 3000: Internal error. Retry is recommended.
 * - 4003: Task is exiting. This can be ignored if returned when calling the stop interface.
 * - 5000: Resource overload. Retry with backoff strategy.
 * - 5001: Concurrency limit reached. Please contact the product team to increase the limit.
 * - -102009: Anchor is not in the room. Please confirm the anchor's status and retry after a delay.
 * - -102005: Room does not exist. Please confirm the room status and retry after a delay.
 */
- (void)onRealtimeTranscriberError:(NSString *)roomId transcriberRobotId:(NSString *)transcriberRobotId error:(NSInteger)error errorInfo:(NSString *)errorInfo;

@end

LITEAV_EXPORT @interface AITranscriberManager : NSObject

/**
 * The AITranscriberManager object cannot be created directly. Use the {@link getAITranscriberManager} interface in TRTCCloud to obtain it.
 */
- (instancetype)init NS_UNAVAILABLE;

/**
 * AI Transcription Interfaces.
 *
 * Start real-time transcription.
 *
 * Enables the AI real-time transcription function to recognize and translate audio from specified users in the room.
 * @param params Transcription parameters, including transcriber robot ID, source language, list of user IDs to transcribe, and target translation languages. For details, please refer to {@link TranscriberParams}.
 * @note
 * 1. Before calling this interface, you need to enable the "Voice to Text" and "Real-time Translation" features in the "Console -> Function Configuration -> Value-added Functions".
 * 2. This interface supports override calls. If you need to update parameters during transcription, you can call this interface directly to overwrite the previous transcription task for the same transcriber robot.
 * 3. After starting the transcription task, if you need to stop it, the initiator must call the stopRealtimeTranscriber interface; other users in the room cannot stop the task. Additionally, if the initiator leaves the room, the transcription task
 * will not stop automatically. It will automatically end only after all users involved in transcription have left the room for more than 30 seconds.
 * 4. If you need the initiator to stop transcription after re-entering the room, we recommend calling the startRealtimeTranscriber interface again to overwrite the transcription task before stopping it.
 */
- (void)startRealtimeTranscriber:(TranscriberParams *)params;

/**
 * Stop real-time transcription.
 *
 * Stops the AI real-time transcription task.
 * @note If the robot ID was not specified when starting transcription, you can pass an empty string when stopping.
 * @param transcriberRobotId Transcriber robot ID
 */
- (void)stopRealtimeTranscriber:(NSString *)transcriberRobotId;

/**
 * Pause receiving transcription messages.
 *
 * After pausing, the SDK will no longer dispatch transcription message callbacks, but the background transcription task will continue, and the SDK will continue to pull transcription data.
 */
- (void)pauseReceivingMessage;

/**
 * Resume receiving transcription messages.
 *
 * After resuming, the SDK will continue to dispatch transcription message callbacks.
 */
- (void)resumeReceivingMessage;

/**
 * Set event callback.
 *
 * Adds a listener for transcription events to receive notifications for real-time transcription and translation.
 * If the transcription task has already been started by other users in the room, you only need to set the event listener to receive real-time transcription and translation messages.
 * @param listener Transcription event listener
 */
- (void)addListener:(id<AITranscriberListener>)listener;

/**
 * Remove event callback.
 *
 * Removes the listener for transcription events. When all listeners are removed, the SDK will stop receiving transcription notifications.
 * @param listener Transcription event listener
 */
- (void)removeListener:(id<AITranscriberListener>)listener;

@end
NS_ASSUME_NONNULL_END
