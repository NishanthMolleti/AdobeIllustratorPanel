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

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil ctx:(SPPluginRef)ctx_
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Initialization code here.
        //msg = msg_;
//        sAIUser->MessageAlert(ai::UnicodeString("panel"));
//        if (msg == 6) {
//            sAIUser->MessageAlert(ai::UnicodeString("panel get 6 msg"));
//            
//        }
        
        
    }
    
    context  = ctx_;
    
    sAIUser->MessageAlert(ai::UnicodeString("init panel"));
    
            if (context) {
                sAIUser->MessageAlert(ai::UnicodeString("panel get 6 msg"));
    
            }
    
    return self;
}

- (IBAction)add:(id)sender
{
    

//    AppContext appContext(_ctx);
//    
//    AIAppContextHandle context = 0;
//    sAIAppContext->PushAppContext(_ctx, &context);

//    if(!_ctx)
//    {
//        sAIUser->MessageAlert(ai::UnicodeString("no context"));
//    }
    
    if (context) {
        sAIUser->MessageAlert(ai::UnicodeString("context set"));
    }
    
    AppContext _context(context);

    
    AIDictionaryRef dict = NULL;
    
    AIErr error = sAIDocument->GetDictionary(&dict);
    
    if (error) {
        sAIUser->MessageAlert(ai::UnicodeString("error"));

    }
    
    if (dict == NULL) {
        sAIUser->MessageAlert(ai::UnicodeString("wew"));
    }else{
        sAIUser->MessageAlert(ai::UnicodeString("wowza"));
    }
    
    const char* stringvalue = "Sample Persistance data.";
    
    std::string sKey("SP");
    
    AIDictKey fStringKey = sAIDictionary->Key(sKey.c_str());
    sAIDictionary->SetStringEntry(dict,fStringKey,stringvalue);
    
    sAIDictionary->Release( dict );
    
    
    
    AIDictionaryRef docDictRef= NULL;
    
    sAIDocument->GetDictionary(&docDictRef);
    
    
    
    AIDictionaryIterator dictionaryIter = NULL;
    
    sAIDictionary->Begin(docDictRef, &dictionaryIter);
    
    
    
    while ( !sAIDictionaryIterator->AtEnd(dictionaryIter) )
        
    {
        
        AIDictKey dictKey = sAIDictionaryIterator->GetKey( dictionaryIter );
        
        const char* keyString = sAIDictionary->GetKeyString(dictKey);
        
        
        
        sAIUser->MessageAlert(ai::UnicodeString(keyString));
        
        
        
        
        
        sAIDictionaryIterator->Next(dictionaryIter);
        
    }
    
    sAIDictionaryIterator->Release( dictionaryIter );
    
    
    
	int value1In = [value1 intValue];
	int value2In = [value2 intValue];
	int outValue = value1In + value2In;
	[output setIntValue:outValue];
}

- (void)setContext:(SPPluginRef)input
{
    sAIUser->MessageAlert(ai::UnicodeString("set context"));

	context = input;
}


@end
