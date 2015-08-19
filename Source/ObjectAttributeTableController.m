//
//  ObjectAttributeTableController.m
//  EmptyPanel
//
//  Created by xcorex on 7/23/15.
//
//

#import "ObjectAttributeTableController.h"

@implementation ObjectAttributeTableController


- (id) init
{
    self = [super init];
    if (self) {
        list = [[NSMutableArray alloc] init];
        
    }
    
    return self;
}

-(NSInteger)numberOfRowsInTableView:(NSTableView *)tableView
{
    return [list count];
}

- (id) tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row
{
    ObjectAttribute * test = [list objectAtIndex:row];
    NSString *identifier = [tableColumn identifier];
    return [test valueForKey:identifier];    
}

- (IBAction)get:(id)sender
{
    sAIUser->MessageAlert(ai::UnicodeString("click"));

    [list addObject:[[ObjectAttribute alloc] init]];
    [tableView reloadData];
}

@end
