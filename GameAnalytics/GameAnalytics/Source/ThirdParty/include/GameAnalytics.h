//
//  GameAnalytics.h
//  GA-SDK-IOS
//
//  Copyright (c) 2015 GameAnalytics. All rights reserved.
//

#pragma once

/*!
 @header GameAnalytics BETA iOS SDK
 @discussion
 <h2>What is GameAnalytics?</h2>
 <p>GameAnalytics is a cloud-hosted solution for tracking, analysis and reporting of game metrics. You can use the services provided by GameAnalytics to store your game-related data directly in the cloud and process, visualize, and analyze it on the fly.</p>

 <h3>Changelog</h3>

 <p>Latest changes</p>
 <ul>
 <li>changed authentication hash method to HMAC</li>
 <li>added method to set engine version from wrapper engines</li>
 <li>altered method naming to conform to apple naming guidelines</li>
 <li>added ‘score’ value to progression events</li>
 <li>minor optimizations</li>
 </ul>
 <p>Current version: 2.0.1</p>

 <h3>Event types</h3>
 <p>We provide a wide range of event types that you can instrument in your game to track the data you're interested in building your analysis from. Here's a brief overview of their uses:</p>
 <p><b>Business</b></p>
 <p>Track any real money transaction in-game. Additionally fetch and attach the in-app purchase receipt.</p>
 <p><b>Resource</b></p>
 <p>Analyze your in-game economy (virtual currencies). You will be able to see the flow (sink/source) for each virtual currency.</p>
 <p><b>Progression</b></p>
 <p>Measure player progression in the game. It follows a 3 hierarchy structure (world, level and phase) to indicate a player's path or place.</p>
 <p><b>Error</b></p>
 <p>Set up custom error events in the game. You can group the events by severity level and attach a message.</p>
 <p><b>Design</b></p>
 <p>Track any type of design event that you want to measure i.e. GUI elements or tutorial steps. <i>Custom dimensions are not supported.</i></p>

 <h3>Download and installation</h3>
 <p>Download the latest version of the GameAnalytics SDK. Add these files to the Xcode project folder:</p>
 <ul>
 <li>GameAnalytics.h - The required header file containing methods for GameAnalytics</li>
 <li>libGameAnalytics.a - The required static library for GameAnalytics</li>
 </ul>

 <h2>Setup</h2>
 <p>In your project "Build Phases" add the following to "Link Binary With Libraries":</p>
 <ul>
 <li>AdSupport.framework</li>
 <li>SystemConfiguration.framework</li>
 <li>libsqlite3.dylib</li>
 <li>libz.dylib</li>
 <li>libGameAnalytics.a (if not already present)</li>
 </ul>

 <h2>Usage</h2>
 <p>You can now use the SDK by adding this in your precompiled header or other places where it's needed:<p>
 <code>#import "GameAnalytics.h"</code>

 <h4>SDK initialize flow</h4>
 <p>GameAnalytics will be activated once initialization method is called. Some methods can only be called <b>before</b> and others <b>after</b> the initialize call.</p>
 <ul>
 <li>Call pre-initialize methods - specifying valid dimension etc.</li>
 <li>Call initialize with the game key and secret key</li>
 <li>Call post-initialize methods - adding events or changing current dimensions.</li>
 </ul>

 <h3>Sessions</h3>
 <p>A new session is started when the SDK is <b>initialized</b> or when the app is <b>resuming from background</b>. When the app is <b>going to background</b> it will attempt to send a "session_end" event. Sometimes the "session_end" cannot be submitted, if the device is offline or it does not have enough time to send it. The next time the app launches this will be detected and a "session_end" will be sent for the previous session.</p>

 <p><b>Please note:</b> when developing locally the simulator/device will stop the app instantly and the "session_end" is often not sent. Therefore when developing locally there might be a "session_end" being submitted almost each time the app is started.</p>

 <h3>Logging</h3>
 <p>When implementing the SDK in Xcode, the console will output information about what is going on.</p>

 <p>These log types will always be available in the log:</p>
 <ul>
 <li>Warning - non-critical unexpected behavior. I.e. parameter validation fail.</li>
 <li>Error - critical errors within the SDK that usually never happen.</li>
 </ul>

 <p>These log types need to be activated:</p>
 <ul>
 <li>InfoLog - This will output compact information when actions are performed by the SDK, i.e. adding/sending events. Use this when implementing the SDK.</li>
 <li>VerboseLog - This will print the full JSON data whenever an event is added.</li>
 </ul>

 <h3>Performance and threading</h3>
 <p>Every action performed by the SDK is added into a thread queue.</p>
 <p>It will therefore handle all processing without blocking the main thread. Each added event will be queued for processing in the same order it was called.</p>

 <h2>Example</h2>
 <p>This is a short example of a typical instrumentation.</p>

 <h3>Initialize the SDK</h3>
 <p>You can place this code in the AppDelegate class in the method "applicationDidFinishLaunchingWithOptions".</p>

 <pre><code>
 // Enable log
 [GameAnalytics setEnabledInfoLog:YES];
 [GameAnalytics setEnabledVerboseLog:NO];

 // Set available virtual currencies and item types
 [GameAnalytics setAvailableResourceCurrencies:@[@"gems", @"gold"]];
 [GameAnalytics setAvailableResourceItemTypes:@[@"boost", @"lives"]];

 // Set available custom dimensions
 [GameAnalytics setAvailableCustomDimensions01:@[@"ninja", @"samurai"]];
 [GameAnalytics setAvailableCustomDimensions02:@[@"whale", @"dolphin"]];
 [GameAnalytics setAvailableCustomDimensions03:@[@"horde", @"alliance"]];

 // Set build version
 [GameAnalytics configureBuild:@"0.1.0"];

 // Initialize
 [GameAnalytics initializeWithGameKey:@"[game key]" gameSecret:@"[secret key]"];
 </code></pre>

 <p><b>Start instrumentation</b></p>
 <p>The methods for adding events become active once the SDK initialization has been called.</p>
 <p>The following is a list of one-liner examples. When implemented in a game they should be called at different parts of the code where the specific action is happening.</p>

 <pre><code>
 // Set dimension (will persist cross session)
 [GameAnalytics setCustomDimension01:@"ninja"];

 // Set progression start (e.g. level start)
 [GameAnalytics addProgressionEventWithProgressionStatus:GAProgressionStatusStart progression01:@"world_01" progression02:@"level_01" progression03:@"wave_01"];

 // Submit virtual currency event
 [GameAnalytics addResourceEventWithFlowType:GAResourceFlowTypeSource currency:@"gold" amount:@10000 itemType:@"boost" itemId:@"big-gold-pack"];
 // Submit custom design event
 [GameAnalytics addDesignEventWithEventId:@"killed:metal_robot" value:@200];
 // Submit error event
 [GameAnalytics addErrorEventWithSeverity:GAErrorSeverityWarning message:@"error detected in user object code. line 606."];

 // Set progression complete (e.g. level end / score screen)
 [GameAnalytics addProgressionEventWithProgressionStatus:GAProgressionStatusComplete progression01:@"world_01" progression02:@"level_01" progression03:@"wave_01" andScore:20000];

 </code></pre>

 */

#include <string>
#include <vector>

namespace gameanalytics {

/*!
 @enum
 @discussion
 This enum is used to specify flow in resource events
 @constant GAResourceFlowTypeSource
 Used when adding to a resource currency
 @constant GAResourceFlowTypeSink
 Used when subtracting from a resource currency
 */
enum GAResourceFlowType
{
	GAResourceFlowTypeSource = 1,
	GAResourceFlowTypeSink = 2
};


/*!
 @enum
 @discussion
 his enum is used to specify status for progression event
 @constant GAProgressionStatusStart
 User started progression
 @constant GAProgressionStatusComplete
 User succesfully ended a progression
 @constant GAProgressionStatusFail
 User failed a progression
 */
enum GAProgressionStatus
{
	GAProgressionStatusStart = 1,
	GAProgressionStatusComplete = 2,
	GAProgressionStatusFail = 3
};


/*!
 @enum
 @discussion
 his enum is used to specify severity of an error event
 @constant GAErrorSeverityDebug
 @constant GAErrorSeverityInfo
 @constant GAErrorSeverityWarning
 @constant GAErrorSeverityError
 @constant GAErrorSeverityCritical
 */
enum GAErrorSeverity
{
	GAErrorSeverityDebug = 1,
	GAErrorSeverityInfo = 2,
	GAErrorSeverityWarning = 3,
	GAErrorSeverityError = 4,
	GAErrorSeverityCritical = 5
};



class GameAnalytics
{
	public:
		/*!
		 @method

		 @abstract Define available 1st custom dimensions

		 @discussion <i>Example usage:</i>
		 <pre><code>
		 NSArray *dimensionArray = @[@"dimA", @"dimB", @"dimC"];<br>
		 [GameAnalytics configureAvailableCustomDimensions01:dimensionArray];
		 </code></pre>

		 @param customDimensions
		 Must be an array of strings.<br>
		 (Array max length=20, String max length=32)

		 @availability Available since 2.0.0

		 @attribute Note! This method must be called before initializing the SDK
		*/
		static void configureAvailableCustomDimensions01(const std::vector<std::string>& customDimensions);

		/*!
		 @method

		 @abstract Set available 2nd custom dimensions

		 @discussion <i>Example usage:</i>
		 <pre><code>
		 NSArray *available = @[@"dimD", @"dimE", @"dimF"];<br>
		 [GameAnalytics configureAvailableCustomDimensions02:dimensionArray;
		 </code></pre>

		 @param customDimensions
		 Must be an array of strings.<br>
		 (Array max length=20, String max length=32)

		 @availability Available since 2.0.0

		 @attribute Note! This method must be called before initializing the SDK
		 */
		static void configureAvailableCustomDimensions02(const std::vector<std::string>& customDimensions);

		/*!
		 @method

		 @abstract Set available 3rd custom dimensions

		 @discussion <i>Example usage:</i>
		 <pre><code>
		 NSArray *available = @[@"dimA", @"dimB", @"dimC"];<br>
		 [GameAnalytics configureAvailableCustomDimensions03:dimensionArray];
		 </code></pre>

		 @param customDimensions
		 Must be an array of strings.<br>
		 (Array max length=20, String max length=32)

		 @availability Available since 2.0.0

		 @attribute Note! This method must be called before initializing the SDK
		 */
		static void configureAvailableCustomDimensions03(const std::vector<std::string>& customDimensions);

		/*!
		 @method

		 @abstract Set available resource currencies

		 @discussion <i>Example usage:</i>
		 <pre><code>
		 NSArray *availableCurrencies = @[@"gems", @"gold"];<br>
		 [GameAnalytics configureAvailableResourceCurrencies:availableCurrencies];
		 </code></pre>

		 @param resourceCurrencies
		 Must be an array of strings.<br>
		 (Array max length=20, String max length=32)

		 @availability Available since 2.0.0

		 @attribute Note! This method must be called before initializing the SDK
		 */
		static void configureAvailableResourceCurrencies(const std::vector<std::string>& resourceCurrencies);

		/*!
		 @method

		 @abstract Set available resource item types

		 @discussion <i>Example usage:</i>
		 <pre><code>
		 NSArray *availableItemTypes = @[@"upgrades", @"powerups"];<br>
		 [GameAnalytics configureAvailableResourceItemTypes:availableItemTypes];
		 </code></pre>

		 @param resourceItemTypes
		 Must be an array of strings.<br>
		 (Array max length=20, String max length=32)

		 @availability Available since 2.0.0

		 @attribute Note! This method must be called before initializing the SDK
		 */
		static void configureAvailableResourceItemTypes(const std::vector<std::string>& resourceItemTypes);

		/*!
		 @method

		 @abstract Set app build version

		 @discussion <i>Example usage:</i>
		 <pre><code>
		 [GameAnalytics configureBuild:@"0.0.1"];
		 </code></pre>

		 @param build
		 (String max length=32)

		 @availability Available since 2.0.0

		 @attribute Note! This method must be called before initializing the SDK
		 */
		static void configureBuild(const std::string& build);

		/* @IF WRAPPER */
		/*
		 Used ONLY by GameAnalytics wrapper SDK's (for example Unity).
		 Never call this manually!
		 */
		static void configureSdkVersion(const std::string& wrapperSdkVersion);
		/* @ENDIF UNITY */

		/*!
		 @method

		 @abstract Set app engine version

		 @discussion <i>Example usage:</i>
		 <pre><code>
		 [GameAnalytics configureEngineVersion:@"unreal 4.8.1"];
		 </code></pre>

		 @param engineVersion
		 (String)

		 @availability Available since 2.0.0

		 @attribute Note! This method must be called before initializing the SDK
		 */
		static void configureEngineVersion(const std::string& engineVersion);

		/*!
		 @method

		 @abstract Initialize GameAnalytics SDK

		 @discussion <i>Example usage:</i>
		 <pre><code>
		 [GameAnalytics initializeWithGameKey:@"123456789ABCDEFGHIJKLMNOPQRSTU" gameSecret:@"123456789ABCDEFGHIJKLMNOPQRSTU12345678"];
		 </code></pre>

		 @param gameKey
		 (String)
		 @param gameSecret
		 (String)

		 @availability Available since 2.0.0
		 */
		static void initializeWithGameKey(const std::string& gameKey,
			const std::string& gameSecret);


		#if !(defined(PLATFORM_IOS) && PLATFORM_IOS) // un unreal we're using different interfac
		/*!
		 @method

		 @abstract Add new business event.

		 @param currency
		 Currency code in ISO 4217 format. (e.g. USD)
		 @param amount
		 Amount in cents (int). (e.g. 99)
		 @param itemType
		 Item Type bought. (e.g. Gold Pack)
		 @param itemId
		 Item bought. (e.g. 1000 gold)

		 @availability Available since 2.0.0

		 @attribute Note! This method cannot be called before initialize method has been triggered
		 */
		static void addBusinessEventWithCurrency(const std::string& currency,
			int amount,
			const std::string& itemType,
			const std::string& itemId,
			const std::string& cartType);

		/*!
		 @method

		 @abstract Add new business event with receipt.

		 @param currency
		 Currency code in ISO 4217 format. (e.g. USD)
		 @param amount
		 Amount in cents (int). (e.g. 99)
		 @param itemType
		 Item Type bought. (e.g. Gold Pack)
		 @param itemId
		 Item bought. (e.g. 1000 gold)
		 @param receipt
		 Transaction receipt string.
		 @param store
		 The store in which the item was bought. Can be one of [apple, google_play].
		 @param signature
		 Transaction signature string in base64. Optional. Only used for Google Play atm.

		 @availability Available since 2.0.0

		 @attribute Note! This method cannot be called before initialize method has been triggered
		 */
		static void addBusinessEventWithCurrency(const std::string& currency,
			int amount,
			const std::string& itemType,
			const std::string& itemId,
			const std::string& cartType,
			const std::string& receipt,
			const std::string& store,
			const std::string& signature = "");

		#else

    	static void addBusinessEventWithCurrency(const std::string& currency,
                                             int amount,
                                             const std::string& itemType,
                                             const std::string& itemId,
                                             const std::string& cartType,
                                      const std::string& receipt);

		static void addBusinessEventWithCurrency(const std::string& currency,
                                             int amount,
                                             const std::string& itemType,
                                             const std::string& itemId,
                                             const std::string& cartType,
                                      bool autoFetchReceipt);

		#endif /* PLATFORM_IOS */


		/*!
		 @method

		 @abstract Add new resource event

		 @param flowType
		 Add or substract resource.<br> (See. GAResourceFlowType)
		 @param currency
		 One of the available currencies set in configureAvailableResourceCurrencies
		 @param amount
		 Amount sourced or sinked
		 @param itemType
		 One of the available currencies set in configureAvailableResourceItemTypes
		 @param itemId
		 Item id (string max length=32)

		 @availability Available since 2.0.0

		 @attribute Note! This method cannot be called before initialize method has been triggered
		 */
		static void addResourceEventWithFlowType(GAResourceFlowType flowType,
			const std::string& currency,
			float amount,
			const std::string&itemType,
			const std::string& itemId);


		/*!
		 @method

		 @abstract Add new progression event

		 @param progressionStatus
		 Status of added progression.<br> (See. GAProgressionStatus)
		 @param progression01
		 1st progression (e.g. world01)
		 @param progression02
		 2nd progression (e.g. level01)
		 @param progression03
		 3rd progression (e.g. phase01)

		 @availability Available since 1.0.0

		 @attribute Note! This method cannot be called before initialize method has been triggered
		 */
		static void addProgressionEventWithProgressionStatus(GAProgressionStatus progressionStatus,
			const std::string& progression01,
			const std::string& progression02,
			const std::string& progression03);

		/*!
		 @method

		 @abstract Add new progression event with score

		 @param progressionStatus
		 Status of added progression.<br> (See. GAProgressionStatus)
		 @param progression01
		 1st progression (e.g. world01)
		 @param progression02
		 2nd progression (e.g. level01)
		 @param progression03
		 3rd progression (e.g. phase01)

		 @availability Available since 2.0.0

		 @attribute Note! This method cannot be called before initialize method has been triggered
		 */
		static void addProgressionEventWithProgressionStatus(GAProgressionStatus progressionStatus,
			const std::string& progression01,
			const std::string& progression02,
			const std::string& progression03,
			int score);

		/*!
		 @method

		 @abstract Add new design event without a value

		 @param eventId
		 String can consist of 1 to 5 segments.<br>
		 Segments are seperated by ':' and segments can have a max length of 32.<br>
		 (e.g. segment1:anotherSegment:gold)

		 @availability Available since 2.0.0

		 @attribute Note! This method cannot be called before initialize method has been triggered
		 */
		static void addDesignEventWithEventId(const std::string& eventId);

		/*!
		 @method

		 @abstract Add new design event with a value

		 @param eventId
		 String can consist of 1 to 5 segments.<br>
		 segments are seperated by ':' and segments can have a max length of 32.<br>
		 (e.g. segment1:anotherSegment:gold)
		 @param value
		 Number value of event

		 @availability Available since 2.0.0

		 @attribute Note! This method cannot be called before initialize method has been triggered
		 */
		static void addDesignEventWithEventId(const std::string& eventId,
			double value);


		/*!
		 @method

		 @abstract Add new error event

		 @param severity
		 Severity of error (See. GAErrorSeverity)
		 @param message
		 Error message (Optional, can be nil)

		 @availability Available since 2.0.0

		 @attribute Note! This method cannot be called before initialize method has been triggered
		 */
		static void addErrorEventWithSeverity(GAErrorSeverity severity,
			const std::string& message);


		/*!
		 @method

		 @abstract Enable info logging to console

		 @param flag
		 Enable or disable info log mode

		 @availability Available since 2.0.0

		 */
		static void setEnabledInfoLog(bool flag);

		/*!
		 @method

		 @abstract Enable verbose info logging of event JSON data to console

		 @param flag
		 Enable or disable verbose info log mode

		 @availability Available since 2.0.0

		 */
		static void setEnabledVerboseLog(bool flag);

		/*!
		 @method

		 @abstract Set 1st custom dimension

		 @param dimension01
		 One of the available dimension values set in configureAvailableCustomDimensions01<br>
		 Will persist cross session. Set to nil to reset.

		 @availability Available since 2.0.0

		 @attribute Note! Must be called after setAvailableCustomDimensions01WithCustomDimensions
		 */
		static void setCustomDimension01(const std::string& dimension01);

		/*!
		 @method

		 @abstract Set 2nd custom dimension

		 @param dimension02
		 One of the available dimension values set in configureAvailableCustomDimensions02<br>
		 Will persist cross session. Set to nil to reset.

		 @availability Available since 2.0.0

		 @attribute Note! Must be called after setAvailableCustomDimensions02
		 */
		static void setCustomDimension02(const std::string& dimension02);

		/*!
		 @method

		 @abstract Set 3rd custom dimension

		 @param dimension03
		 One of the available dimension values set in configureAvailableCustomDimensions03<br>
		 Will persist cross session. Set to nil to reset.

		 @availability Available since 2.0.0

		 @attribute Note! Must be called after setAvailableCustomDimensions03W
		 */
		static void setCustomDimension03(const std::string& dimension03);

		/*!
		 @method

		 @abstract Set user facebook id

		 @param facebookId
		 Facebook id of user (Persists cross session)

		 @availability Available since 2.0.0
		 */
		static void setFacebookId(const std::string& facebookId);

		/*!
		 @method

		 @abstract Set user gender

		 @param gender
		 Gender of user (Persists cross session)<br>
		 Must be one of (male / female)

		 @availability Available since 2.0.0
		 */
		static void setGender(const std::string& gender);

		/*!
		 @method

		 @abstract Set user birth year

		 @param birthYear
		 Birth year of user (Persists cross session)

		 @availability Available since 2.0.0
		 */
		static void setBirthYear(int birthYear);

	private:
		static bool internalInitialize();

		static bool isSdkReadyWithNeedsInitialized(bool needsInitialized);
		static bool isSdkReadyWithNeedsInitialized(bool needsInitialized, bool warn);
		static bool isSdkReadyWithNeedsInitialized(bool needsInitialized, bool warn, std::string message);
};

}
