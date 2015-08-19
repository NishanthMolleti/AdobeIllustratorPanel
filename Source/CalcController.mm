//========================================================================================
//  
//  $File: $
//
//  $Revision: $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================

#import "CalcController.h"


@implementation CalcController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil ctx:(SPPluginRef)ctx_ {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        sAIUser->MessageAlert(ai::UnicodeString("init set context"));
        list = [[NSMutableArray alloc] init];
        context  = ctx_;
    }
    return self;
}

-(void)awakeFromNib {
    AIErr error = kNoErr;

    list = [[NSMutableArray alloc] init];    
    
    [ObjectAttributeController sharedInstance];

}


- (IBAction)add:(id)sender
{
    

//    AppContext appContext(_ctx);
//    
//    AIAppContextHandle context = 0;
//    sAIAppContext->PushAppContext(_ctx, &context);

    if(!context)
    {
        sAIUser->MessageAlert(ai::UnicodeString("no context"));
        return;
    }



    AppContext _context(context);
    
//    AIArtHandle **artStore = NULL;
//    
//    int artCount = 0;
//    
//    sAIMatchingArt->GetSelectedArt(&artStore, &artCount);
//    
//        if (artCount > 3) {
//            sAIUser->MessageAlert(ai::UnicodeString("artCount > 3"));
//    
//        }
//
//    AIArtHandle my_artHandle = (*artStore)[0];
//    AIDictionaryRef artDict;
//    
//    sAIArt->GetDictionary(my_artHandle, &artDict);
//    
//    sAIDictionary->SetStringEntry(artDict,sAIDictionary->Key("openframeworks"),"opengl parameter");
//
//
//    sAIDictionary->Release(artDict);
//    
//    AIErr err;
//
//    ai::FilePath svgFile;
//    
//    err = sAIFilePath->NewFilePath(svgFile);
//    
//    err = sAIFilePath->Set(ai::UnicodeString("/Users/xcorex/tmp.svg"), true, svgFile);
//    
//    err = sAIDocument->WriteDocument(svgFile, kAISVGFileFormat, false);
    
    
    
    
//    
//    AIDictionaryRef dict = NULL;
//    
//    AIErr error = sAIDocument->GetDictionary(&dict);
//    
//    if (error) {
//        sAIUser->MessageAlert(ai::UnicodeString("error"));
//    }
//    
//    if (dict == NULL) {
//        sAIUser->MessageAlert(ai::UnicodeString("NULL"));
//    }
//
//    const char* stringvalue = "Sample Persistance data.";
//    
//    std::string sKey("SP");
//    
//    AIDictKey fStringKey = sAIDictionary->Key(sKey.c_str());
//    sAIDictionary->SetStringEntry(dict,fStringKey,stringvalue);
//    
//    sAIDictionary->Release( dict );
//    
//    AIArtHandle my_artHandle = (*artStore)[0];
//    AIDictionaryRef artDict;
//    
//    sAIArt->GetDictionary(my_artHandle, &artDict);
    
    
  
    AIDictionaryRef docDictRef= NULL;
    
    sAIDocument->GetDictionary(&docDictRef);
    
    
    
    AIDictionaryIterator dictionaryIter = NULL;
    
    sAIDictionary->Begin(docDictRef, &dictionaryIter);
    
    
    
    while ( !sAIDictionaryIterator->AtEnd(dictionaryIter) )
        
    {
        
        AIDictKey dictKey = sAIDictionaryIterator->GetKey( dictionaryIter );
        
        const char* keyString = sAIDictionary->GetKeyString(dictKey);
        
        AIEntryType entryType;
        
        sAIDictionary->GetEntryType(docDictRef,  dictKey , &entryType);
        
        
        
        if(entryType == StringType){

            ObjectAttribute * _val = [[ObjectAttribute alloc] init];
            
            const char * buffer;
            
            sAIDictionary->GetStringEntry(docDictRef,  dictKey , &buffer);
            
            _val.name = [NSString stringWithUTF8String:keyString];;
            _val.value = [NSString stringWithUTF8String:buffer];;
            
            
            
            [list addObject:_val];
            
        }
        
        //sAIUser->MessageAlert(ai::UnicodeString(keyString));
        
        
    
        
        sAIDictionaryIterator->Next(dictionaryIter);
        
    }
    
    sAIDictionaryIterator->Release( dictionaryIter );
  
    [tableView reloadData];

}

- (void)setContext:(SPPluginRef)input
{
	context = input;
}



- (IBAction)set:(id)sender {
    
    AppContext _context(context);

    AIArtHandle **artStore = NULL;
    int artCount = 0;

    sAIMatchingArt->GetSelectedArt(&artStore, &artCount);

    AIArtHandle my_artHandle = (*artStore)[1];
    
    AIDictionaryRef artDict;

    sAIArt->GetDictionary(my_artHandle, &artDict);

    sAIDictionary->SetStringEntry(artDict,sAIDictionary->Key("openframeworks"),"opengl parameter");

    sAIDictionary->Release(artDict);
}


- (void)get:(id)sender
{
    
    AppContext _context(context);

    AIDictionaryRef artDict;
    AIArtHandle **artStore = NULL;
    
    int artCount = 0;
    sAIMatchingArt->GetSelectedArt(&artStore, &artCount);

    AIArtHandle my_artHandle = (*artStore)[1];
    
    AIDictionaryIterator dictionaryIter = NULL;
    
    sAIArt->GetDictionary(my_artHandle, &artDict);

    
    sAIDictionary->Begin(artDict, &dictionaryIter);
    
    
    while ( !sAIDictionaryIterator->AtEnd(dictionaryIter) )
        
    {
        
        AIDictKey dictKey = sAIDictionaryIterator->GetKey( dictionaryIter );
//
        const char* keyString = sAIDictionary->GetKeyString(dictKey);
//
        AIEntryType entryType;
//
        sAIDictionary->GetEntryType(artDict,  dictKey , &entryType);
//
//        
//        
        if(entryType == StringType){
//
//            ObjectAttribute * _val = [[ObjectAttribute alloc] init];
//            
            const char * buffer;
//
            sAIDictionary->GetStringEntry(artDict,  dictKey , &buffer);
//
//            _val.name = [NSString stringWithUTF8String:keyString];;
//            _val.value = [NSString stringWithUTF8String:buffer];;
//            
//            
//            
//            [list addObject:_val];
//
            sAIUser->MessageAlert(ai::UnicodeString(keyString));
            sAIUser->MessageAlert(ai::UnicodeString(buffer));

        }
//
        
        
        
        
        sAIDictionaryIterator->Next(dictionaryIter);
        
    }
    
    sAIDictionaryIterator->Release( dictionaryIter );

    

    
    
}

-(NSInteger)numberOfRowsInTableView:(NSTableView *)tableView {
    return [list count];
}

- (id) tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    ObjectAttribute * test = [list objectAtIndex:row];
    NSString *identifier = [tableColumn identifier];
    return [test valueForKey:identifier];
}

- (void)tableView:(NSTableView *)tableView setObjectValue:(id)object forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    
}


@end
