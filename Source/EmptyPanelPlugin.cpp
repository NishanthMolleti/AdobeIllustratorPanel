//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/EmptyPanel/source/EmptyPanelPlugin.cpp $
//
//  $Revision: #2 $
//
//  Copyright 1987 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//========================================================================================
#ifdef MAC_ENV
#include <Cocoa/Cocoa.h>
#include "CalcController.h"
#include "BarController.h"
#endif


#include "IllustratorSDK.h"
#include "EmptyPanelPlugin.h"
#include "EmptyPanelPluginSuites.h"
#include "EmptyPanleID.h"


#define bufMax 1024
#define controlBarHeight	40
#define controlBarWidth		800
#define controlBarWidthMin	50
#define controlBarWidthMax	1200
#define CHECK_ERROR  if (error) {return error;}

extern "C" SPBasicSuite*  sSPBasic;

#ifdef MAC_ENV
NSView* nibView = nil;
NSView* controlPanelNibView = nil;
#endif

Plugin *AllocatePlugin(SPPluginRef pluginRef)
{
	return new EmptyPanelPlugin(pluginRef);
}

void FixupReload(Plugin *plugin)
{
	EmptyPanelPlugin::FixupVTable( static_cast<EmptyPanelPlugin*>( plugin ) );
}

EmptyPanelPlugin::EmptyPanelPlugin(SPPluginRef pluginRef)
	: Plugin(pluginRef),
	fPanel(NULL),
	hDlg(NULL)
{
	strncpy(fPluginName, kEmptyPanelPluginName, kMaxStringLength);
	
}

static void flyoutMenuPreVisFunc(AIPanelRef inPanel)
{
	sAIUser->MessageAlert(ai::UnicodeString("pre visiblity"));
}

void PanelFlyoutMenuProc(AIPanelRef inPanel, ai::uint32 itemID)
{
	AIErr error = kNoErr;
	AIPanelFlyoutMenuRef flyoutMenu = NULL;
	error = sAIPanel->GetFlyoutMenu(inPanel, flyoutMenu);
	AIPanelFlyoutMenuItemMark currentItemMark;
	switch(itemID)
	{
	case 1:
		error = sAIPanelFlyoutMenu->GetItemMark(flyoutMenu, 1 , currentItemMark);
		error = sAIPanelFlyoutMenu->SetItemMark(flyoutMenu, 1 , currentItemMark ? kAIPanelFlyoutMenuItemMark_NONE : kAIPanelFlyoutMenuItemMark_BULLET);
		break;
	case 2:
		error = sAIPanelFlyoutMenu->GetItemMark(flyoutMenu, 2 , currentItemMark);
		error = sAIPanelFlyoutMenu->SetItemMark(flyoutMenu, 2 , currentItemMark ? kAIPanelFlyoutMenuItemMark_NONE : kAIPanelFlyoutMenuItemMark_CHECK);
		break;
	case 3:
		error = sAIPanelFlyoutMenu->GetItemMark(flyoutMenu, 3 , currentItemMark);
		error = sAIPanelFlyoutMenu->SetItemMark(flyoutMenu, 3 , currentItemMark ? kAIPanelFlyoutMenuItemMark_NONE : kAIPanelFlyoutMenuItemMark_DASH);
		break;
	}
}

void PanelVisibilityChangedNotifyProc(AIPanelRef inPanel, AIBoolean isVisible)
{
	AIPanelUserData ud = NULL;
	sAIPanel->GetUserData(inPanel, ud);
	EmptyPanelPlugin* sPlugin = reinterpret_cast<EmptyPanelPlugin*>(ud);
	sPlugin->UpdateMenu(isVisible, PANEL);
}

void PanelSizeChangedNotifyProc(AIPanelRef inPanel)
{
#ifdef MAC_ENV
	AISize panelSize= {0,0};
	AIErr error = kNoErr;
	
	error = sAIPanel->GetSize(inPanel, panelSize);
	
	if(!error)
	{
		NSRect newRect = NSMakeRect(0,0,panelSize.width,panelSize.height);
		[nibView setFrame:newRect];
	}
#endif
}	

void PanelStateChangedNotifyProc(AIPanelRef inPanel, ai::int16 newState)
{
	AIErr err = kNoErr;
	AISize prefSize;
	switch(newState)
	{
	case 1:
		prefSize.height = prefSize.width = 300;
		break;
	case 2:
		prefSize.height = prefSize.width = 500;
		break;
	case 3:
		prefSize.height = prefSize.width = 700;
		break;
	}
	
	err = sAIPanel->SetPreferredSizes(inPanel, prefSize);
}

void PanelClosedNotifyProc(AIPanelRef inPanel)
{
	sAIUser->MessageAlert(ai::UnicodeString("Panel Closed"));
}

//--------------------------------------------------------------------
//Callback Procedures for Control Bar
//--------------------------------------------------------------------
void ControlBarVisibilityChangedNotifyProc(AIControlBarRef inControlBar, AIBoolean isVisible)
{
	AIErr err = kNoErr;

	AIControlBarUserData userData = NULL;
	err = sAIControlBar->GetUserData(inControlBar, userData);
	if(err == kNoErr && userData)
	{
		EmptyPanelPlugin* plugin = reinterpret_cast<EmptyPanelPlugin*>(userData);
		plugin->UpdateMenu(isVisible, CTRL_BAR);
	}
}

void ControlBarSizeChangedNotifyProc(AIControlBarRef inControlBar)
{

}

// --------------------------------------------------------------------
// Called when plugin is initially loaded
// --------------------------------------------------------------------
ASErr EmptyPanelPlugin::StartupPlugin(SPInterfaceMessage *message)
{
	AIErr err = kNoErr;
	
	// Call base class routine
	err = Plugin::StartupPlugin(message);
	if (err)
		return err;

	AINotifierHandle appShutDownNotifier;
	err = sAINotifier->AddNotifier(fPluginRef, "AI Application Shutdown Notifier", kAIApplicationShutdownNotifier, &appShutDownNotifier);
	if(err)
		return err;
	
	AIErr error = kNoErr;

	// Add About Plugins menu item for this plug-in.
	SDKAboutPluginsHelper aboutPluginsHelper;
	error = aboutPluginsHelper.AddAboutPluginsMenuItem(message, 
				kSDKDefAboutSDKCompanyPluginsGroupName, 
				ai::UnicodeString(kSDKDefAboutSDKCompanyPluginsGroupNameString), 
				"EmptyPanel...", 
				&fAboutPluginMenu);

	if (error)
		return error;

	// Add menu item
	error = sAIMenu->AddMenuItemZString(fPluginRef, "Third Party Panel", kOtherPalettesMenuGroup, ZREF("Third Party Panel"),
										kMenuItemNoOptions, &fEmptyPanelPanelMenuItemHandle);
	if (error)
		return error;

	fPanelFlyoutMenu = NULL;
	error = sAIPanelFlyoutMenu->Create(fPanelFlyoutMenu);
	if (error)
		return error;

	error = sAIPanelFlyoutMenu->AppendItem(fPanelFlyoutMenu, 1, ai::UnicodeString("First Item"));
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->AppendItem(fPanelFlyoutMenu, 3, ai::UnicodeString("Third Item"));
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->InsertItem(fPanelFlyoutMenu, 3, 2, ai::UnicodeString("Second Item"));
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->InsertSeparator(fPanelFlyoutMenu, 3, 5);
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->AppendItem(fPanelFlyoutMenu, 4, ai::UnicodeString("Fourth Item"));
    CHECK_ERROR
    
	error = sAIPanelFlyoutMenu->SetItemEnabled(fPanelFlyoutMenu, 4, false);
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->SetItemMark(fPanelFlyoutMenu, 1 , kAIPanelFlyoutMenuItemMark_BULLET);
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->SetItemMark(fPanelFlyoutMenu, 2 , kAIPanelFlyoutMenuItemMark_CHECK);
    CHECK_ERROR
	error = sAIPanelFlyoutMenu->SetItemMark(fPanelFlyoutMenu, 3 , kAIPanelFlyoutMenuItemMark_DASH);
	CHECK_ERROR
    
	AISize pnSize = {240, 320};
	error = sAIPanel->Create(fPluginRef, ai::UnicodeString("Third Party Panel"), ai::UnicodeString("Third Party Panel"), 3, pnSize, true, fPanelFlyoutMenu, this, fPanel);
	CHECK_ERROR

	AISize minSize = {50, 50};
	AISize maxSize = {800, 800};
	AISize prefConstSize = {100, 100};
	AISize prefUnconstSize = {600, 600};

	error = sAIPanel->SetSizes(fPanel, minSize, prefUnconstSize, prefConstSize, maxSize);
	CHECK_ERROR
	error = sAIPanel->Show(fPanel, true);
      CHECK_ERROR
	error = sAIPanel->SetFlyoutMenuPreVisibilityProc(fPanel, flyoutMenuPreVisFunc);
      CHECK_ERROR
	error = sAIPanel->SetFlyoutMenuProc(fPanel, PanelFlyoutMenuProc);
      CHECK_ERROR
	error = sAIPanel->SetVisibilityChangedNotifyProc(fPanel, PanelVisibilityChangedNotifyProc);
      CHECK_ERROR
	error = sAIPanel->SetSizeChangedNotifyProc(fPanel, PanelSizeChangedNotifyProc);
      CHECK_ERROR
	error = sAIPanel->SetStateChangedNotifyProc(fPanel, PanelStateChangedNotifyProc);
      CHECK_ERROR
	error = sAIPanel->SetClosedNotifyProc(fPanel, PanelClosedNotifyProc);
	CHECK_ERROR
    
	error = SetIcon();
      CHECK_ERROR

	error = AddWidgets();
	
	//Add Menu Item for Control Bar
	if(!error)
		error = sAIMenu->AddMenuItemZString(fPluginRef, "Third Party Control Bar", kOtherPalettesMenuGroup, ZREF("Third Party Control Bar"),
											kMenuItemNoOptions, &fEmptyPanelControlBarMenuItemHandle);
	
	//Create Control Bar
	AISize sizeControlBar = {controlBarWidth, controlBarHeight};
	if(!error)
		error = sAIControlBar->Create(fPluginRef, sizeControlBar, controlBarWidthMin, controlBarWidthMax,NULL/*Userdata*/,fControlBar);
	if(!error)
		error = sAIControlBar->SetUserData(fControlBar, this);
	
	//Set Callbacks
	if(!error)
		error = sAIControlBar->SetVisibilityChangedNotifyProc(fControlBar, ControlBarVisibilityChangedNotifyProc);
	if(!error)
		error = sAIControlBar->SetSizeChangedNotifyProc(fControlBar, ControlBarSizeChangedNotifyProc);
	
	//Add Different Widgets to Control Bar
	if(!error)
		AddWidgetsToControlBar();
	
	return error;
}

AIErr EmptyPanelPlugin::AddWidgets()
{
	AIErr error = kNoErr;
	AIPanelPlatformWindow hDlg = NULL;
	error = sAIPanel->GetPlatformWindow(fPanel, hDlg);

	
#ifdef MAC_ENV
	// Get our own bundle
	NSBundle* bundle = [NSBundle bundleWithIdentifier:@"com.adobe.illustrator.plugins.EmptyPanel"];
	//load the nib file
	CalcController* calculator = [CalcController alloc];
    
    //here
    //AppContext appContext(GetPluginRef());
    
    
    
    //here
    
    
	[calculator initWithNibName:@"View" bundle:bundle ctx:GetPluginRef()];
	//set panel to be our nibs view
    

	NSView* newView = [calculator view];
	[hDlg setFrame:[newView frame]];
	[hDlg addSubview:newView];
	[calculator setContext:GetPluginRef()];
    
#endif
	return error;
}

AIErr EmptyPanelPlugin::AddWidgetsToControlBar()
{
	AIErr error = kNoErr;
	AIControlBarPlatformWindow ctrlBarPlatformWindow = NULL;
	
	error = sAIControlBar->GetPlatformWindow(fControlBar, ctrlBarPlatformWindow);

	if (error)
		return error;
	
	if(ctrlBarPlatformWindow)
	{
		
        #ifdef MAC_ENV
		
		//Uncomment this section for code that does not use a nib (not recommended)
		/* 
		NSRect widthTextEditFrame = NSMakeRect(10, 10, 70, 18);
		NSTextField* widthTextEditField = [[NSTextField alloc] initWithFrame:widthTextEditFrame];
		[ctrlBarPlatformWindow addSubview:widthTextEditField];
		
		NSRect minWidthTextEditFrame = NSMakeRect(85, 10, 40, 18);
		NSTextField* minWidthTextEditField = [[NSTextField alloc] initWithFrame:minWidthTextEditFrame];
		[ctrlBarPlatformWindow addSubview:minWidthTextEditField];
		
		NSRect commitButtonFrame = NSMakeRect(130, 8, 60, 22);
		NSButton *commitButton = [[NSButton alloc] initWithFrame:commitButtonFrame];
		[commitButton setTitle:@"Commit"];
		[ctrlBarPlatformWindow addSubview:commitButton]; 
		 
		 */
		
		//Uncomment below for example loading nib without NSViewController (CalcController classes)
		/*
		NSBundle* bundle = [NSBundle bundleWithIdentifier:@"com.adobe.illustrator.plugins.EmptyPanel"];
		
		// Replace "View" with your own nib file
		NSNib*      aNib = [[NSNib alloc] initWithNibNamed:@"ControlPanel" bundle:bundle];
		NSArray*    topLevelObjs = nil;
		
		// ***** Loads Nib ******
		if (![aNib instantiateNibWithOwner:ctrlBarPlatformWindow topLevelObjects:&topLevelObjs])
		{
			NSLog(@"Warning! Could not load nib file.\n");
			return nil;
		}
		
		for(id topView in topLevelObjs)
		{
			if([topView isKindOfClass:[NSView class]])
			{
				controlPanelNibView = topView;
				break;
			}
		}
		
		//This could also be done from IB
		[controlPanelNibView setAutoresizingMask:0];
		[ctrlBarPlatformWindow setFrame:[controlPanelNibView frame]];
		[ctrlBarPlatformWindow addSubview:controlPanelNibView];
		[controlPanelNibView release];*/
		
		NSBundle* bundle = [NSBundle bundleWithIdentifier:@"com.adobe.illustrator.plugins.EmptyPanel"];
		BarController* barcontroller = [BarController alloc];
		[barcontroller initWithNibName:@"ControlPanel" bundle:bundle];
		
		NSView* newView = [barcontroller view];
		
		[ctrlBarPlatformWindow setFrame:[newView frame]];
		[ctrlBarPlatformWindow addSubview:newView];
		[barcontroller setControlBarRef:fControlBar];
        [barcontroller setCtx:GetPluginRef()];

        
        
#endif
	}
	return error;
}


ASErr EmptyPanelPlugin::ShutdownPlugin(SPInterfaceMessage *message)
{
	AIErr error = kNoErr;
	if(fPanel)
	{
		error = sAIPanel->Destroy(fPanel);
		fPanel = NULL;
	}
	if(fPanelFlyoutMenu)
	{
		error = sAIPanelFlyoutMenu->Destroy(fPanelFlyoutMenu);
		fPanelFlyoutMenu = NULL;
	}
	return kNoErr;
}

ASErr EmptyPanelPlugin::GoMenuItem(AIMenuMessage *message)
{
	AIErr error = kNoErr;
	if (message->menuItem == fAboutPluginMenu) 
	{
		SDKAboutPluginsHelper aboutPluginsHelper;
		aboutPluginsHelper.PopAboutBox(message, "About EmptyPanel", kSDKDefAboutSDKCompanyPluginsAlertString);
	}
	else if (message->menuItem == fEmptyPanelPanelMenuItemHandle)
	{	
		if(fPanel)
		{
			AIBoolean isShown = false;
			error = sAIPanel->IsShown(fPanel, isShown);
			error = sAIPanel->Show(fPanel, !isShown);
		}
	}
	else if (message->menuItem == fEmptyPanelControlBarMenuItemHandle)
	{
		if(fControlBar)
		{
			AIBoolean isShown = false;
			error = sAIControlBar->IsShown(fControlBar,isShown);
			error = sAIControlBar->Show(fControlBar, !isShown);
		}
	}
	return error;
}

void EmptyPanelPlugin::UpdateMenu(AIBoolean isVisible, ItemType item)
{
	if (item == PANEL)
		sAIMenu->CheckItem (fEmptyPanelPanelMenuItemHandle , isVisible);
	else if (item == CTRL_BAR)
		sAIMenu->CheckItem (fEmptyPanelControlBarMenuItemHandle, isVisible);
}

ASErr EmptyPanelPlugin::Notify(AINotifierMessage *message)
{
	AIErr result = kNoErr;
	if(strcmp(message->type, kAIApplicationShutdownNotifier) == 0)
	{
		
		if(fPanel)
		{
		

			result = sAIPanel->Destroy(fPanel);
			fPanel = NULL;
		}
		if(fPanelFlyoutMenu)
		{
			result = sAIPanelFlyoutMenu->Destroy(fPanelFlyoutMenu);
			fPanelFlyoutMenu = NULL;
		}
		if (fControlBar != NULL)
		{

			result = sAIControlBar->Destroy(fControlBar);
			fControlBar = NULL;
		}
	}
	return result;
}

ASErr EmptyPanelPlugin::SetIcon()
{
	   AIErr error = kNoErr;
       ai::AutoBuffer<ai::uint32> iconResID(1), darkIconResID(1);
       iconResID[(size_t)0] = 16200;
       darkIconResID[(size_t)0] = 16200;
       error = sAIPanel->SetIconResourceID( fPanel, iconResID, darkIconResID );
       return error;
}

ASErr EmptyPanelPlugin::GetIcon(AIDataFilter* dataFilterIn, string* buffStrIn, size_t* lenIn)
{
    AIErr error = kNoErr;
    AIDataFilterSuite* sAIDataFilter = NULL;
	error = sSPBasic->AcquireSuite(kAIDataFilterSuite, kAIDataFilterVersion, (const void **)&sAIDataFilter);

    error = sAIDataFilter->LinkDataFilter(NULL, dataFilterIn);
    
    char buf[bufMax];
    
    for(;;)
    {
        size_t count = bufMax;
        const ASErr error = sAIDataFilter->ReadDataFilter(dataFilterIn, buf, &count);
        if (error)
        {
            return error;
        }
        *lenIn += count;
        buffStrIn->append(buf, count);
        if (count != bufMax)
        {
            break;
        }
    }
}
