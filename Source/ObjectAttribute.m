//
//  ObjectAttribute.m
//  EmptyPanel
//
//  Created by xcorex on 7/23/15.
//
//

#import "ObjectAttribute.h"

@implementation ObjectAttribute

@synthesize value;
@synthesize name;


- (id) init
{
    self = [super init];
    if (self) {
        name =@"Position";
        value = @"Center";
    }
    
    return self;
}


- (void) dealloc
{
    [super dealloc];
}


@end
