//
//  ObjectAttributeController.m
//  EmptyPanel
//
//  Created by xcorex on 8/19/15.
//
//

#import "ObjectAttributeController.h"

@implementation ObjectAttributeController {
    NSMutableArray * attributes;
}

- (instancetype)init
{
    self = [super init];
    if (self) {
        attributes = [[NSMutableArray alloc] init];
    }
    return self;
}

+ (instancetype) sharedInstance {
    static dispatch_once_t once;
    static id _sharedInstance = nil;
    dispatch_once(&once, ^{
        _sharedInstance = [[self alloc] init];
    });
    return _sharedInstance;
}

@end
