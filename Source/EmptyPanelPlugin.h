//========================================================================================
//  
//  $File: //ai/mainline/devtech/sdk/public/samplecode/EmptyPanel/source/EmptyPanelPlugin.h $
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

#ifndef __EmptyPanelPlugin_H__
#define __EmptyPanelPlugin_H__

#include "Plugin.hpp"
#include "AIPanel.h"
#include "AIControlBar.h"
#include "SDKDef.h"
#include "SDKAboutPluginsHelper.h"



Plugin *AllocatePlugin(SPPluginRef pluginRef);
void FixupReload(Plugin *plugin);

enum ItemType {
	PANEL,
	CTRL_BAR
};

class EmptyPanelPlugin : public Plugin
{
public:

	EmptyPanelPlugin(SPPluginRef pluginRef);
	virtual ~EmptyPanelPlugin() {}
	
	virtual ASErr StartupPlugin(SPInterfaceMessage *message); 
	virtual ASErr ShutdownPlugin(SPInterfaceMessage *message); 

	void UpdateMenu(AIBoolean isVisible, ItemType item);
	ASErr GoMenuItem(AIMenuMessage *message);
	ASErr Notify(AINotifierMessage *message);

	FIXUP_VTABLE_EX(EmptyPanelPlugin, Plugin);

private:
	
	/**	Handle for the About SDK Plug-ins menu item.
	*/
	AIMenuItemHandle fAboutPluginMenu;

	/** Handle for menu item in Window > Third Party Panel menu item.
	*/
	AIMenuItemHandle fEmptyPanelPanelMenuItemHandle;

	/** Pointer to instance of Panel.
	*/
	AIPanelRef fPanel;

	AIPanelFlyoutMenuRef fPanelFlyoutMenu;

	AIControlBarRef fControlBar;

	AIMenuItemHandle fEmptyPanelControlBarMenuItemHandle;
	
	ASErr SetIcon();
    
    ASErr GetIcon(AIDataFilter* dataFilterIn, string* buffStrIn, size_t* lenIn);

	ASErr AddWidgets();
	
	ASErr AddWidgetsToControlBar();

	AIPanelPlatformWindow hDlg;

};

#endif	// __EmptyPanelPlugin_H__
