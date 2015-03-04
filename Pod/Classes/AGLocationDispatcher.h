//
//  AGLocationDispatch.h
//  LocationDispatch
//
//  Created by Vladimir Zgonik on 09.02.15.
//  Copyright (c) 2015 Agilie. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import "AGLocation.h"

@protocol AGLocationServiceDelegate<NSObject>

@optional

@end

typedef void(^SenderBlock)(id data);

typedef void(^AGLocationServiceAuthorizationStatusChangeBlock)(CLLocationManager *manager, CLAuthorizationStatus status);

typedef void(^AGLocationServiceLocationUpdateBlock)(CLLocationManager *manager, AGLocation *newLocation, AGLocation *oldLocation);

typedef void(^AGLocationServiceLocationAndSpeedUpdateBlock)(CLLocationManager *manager, AGLocation *newLocation, AGLocation *oldLocation, NSNumber *speed);

typedef void(^AGLocationServiceLocationUpdateFailBlock)(CLLocationManager *manager, NSError *error);

@interface AGLocationDispatcher : NSObject <CLLocationManagerDelegate>

@property (strong, nonatomic) AGLocation *location;
@property (assign, nonatomic) NSTimeInterval locationUpdateInterval;
@property (assign, nonatomic) BOOL locationObtained;

+ (BOOL)locationServicesEnabled;
+ (BOOL)significantLocationChangeMonitoringAvailable;

- (instancetype)init;

- (instancetype)initWithUpdatingInterval:(NSTimeInterval)interval andDesiredAccuracy:(CLLocationAccuracy)horizontalAccuracy;

// To receive continuous updates on the authorization status and ask once user has allowed location services.
- (void)requestUserLocationWhenInUseWithBlock:(AGLocationServiceAuthorizationStatusChangeBlock)block;

- (void)requestUserLocationAlwaysWithBlock:(AGLocationServiceAuthorizationStatusChangeBlock)block;

// get current position in AGLocationServiceLocationUpdateBlock (CLLocationManager *manager, AGLocation *newLocation, AGLocation *oldLocation) once
- (void)currentLocationWithBlock:(AGLocationServiceLocationUpdateBlock)block errorBlock:(AGLocationServiceLocationUpdateFailBlock)errorBlock;

// get current position every time interval in AGLocationServiceLocationUpdateBlock (CLLocationManager *manager, AGLocation *newLocation, AGLocation *oldLocation)
- (void)startUpdatingLocationWithBlock:(AGLocationServiceLocationUpdateBlock)block errorBlock:(AGLocationServiceLocationUpdateFailBlock)errorBlock;

// get current position and speed every time interval in AGLocationServiceLocationAndSpeedUpdateBlock (CLLocationManager *manager, AGLocation *newLocation, AGLocation *oldLocation, NSNumber *speed)
- (void)startUpdatingLocationAndSpeedWithBlock:(AGLocationServiceLocationAndSpeedUpdateBlock)block errorBlock:(AGLocationServiceLocationUpdateFailBlock)errorBlock;

@end