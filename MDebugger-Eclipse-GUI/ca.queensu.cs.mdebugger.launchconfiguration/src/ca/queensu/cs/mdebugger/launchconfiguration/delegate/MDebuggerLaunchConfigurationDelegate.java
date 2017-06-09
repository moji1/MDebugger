/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: this code creates a launch configuration for MDebugger
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 ******************************************************************************/

package ca.queensu.cs.mdebugger.launchconfiguration.delegate;

import org.eclipse.core.resources.IResource;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.debug.core.DebugPlugin;
import org.eclipse.debug.core.ILaunch;
import org.eclipse.debug.core.ILaunchConfiguration;
import org.eclipse.debug.core.ILaunchConfigurationType;
import org.eclipse.debug.core.ILaunchConfigurationWorkingCopy;
import org.eclipse.debug.core.ILaunchManager;
import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.debug.core.model.LaunchConfigurationDelegate;
import org.eclipse.debug.ui.ILaunchShortcut;
import org.eclipse.debug.ui.ILaunchShortcut2;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.ui.IEditorPart;

import ca.queensu.cs.mdebugger.debugger.model.MDebuggerDebugTarget;

public class MDebuggerLaunchConfigurationDelegate extends LaunchConfigurationDelegate implements ILaunchShortcut, ILaunchShortcut2{

	public MDebuggerLaunchConfigurationDelegate() {
		// TODO Auto-generated constructor stub
	}

	@Override
	public void launch(ILaunchConfiguration configuration, String mode, ILaunch launch, IProgressMonitor monitor)
			throws CoreException {
	//	String attribute = configuration.getAttribute(MDebuggerConfigurationAttributes.CONSOLE_TEXT, "Simon says \"RUN!\"");
    //    System.out.println(attribute);
		
		
        if (ILaunchManager.DEBUG_MODE.equals(mode)) {
        	IDebugTarget target = new MDebuggerDebugTarget(null, launch); // instantiate custom IDebugTarget
//        	 TCPServerProcess process = new TCPServerProcess(target);
//        	 target.setProcess(process);
             launch.addDebugTarget(target);
        }
	}

	@Override
	public void launch(ISelection selection, String mode) {
		// TODO Auto-generated method stub
	}

	@Override
	public void launch(IEditorPart editor, String mode) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public ILaunchConfiguration[] getLaunchConfigurations(ISelection selection) {
		// TODO Auto-generated method stub
		
		IResource resource = this.getLaunchableResource(selection);
		ILaunchManager manager = DebugPlugin.getDefault().getLaunchManager();
		
		ILaunchConfigurationType type = manager.getLaunchConfigurationType("ca.queensu.cs.mdebugger.launchconfiguration.launchConfigurationType");
		try {
			ILaunchConfiguration[] configurations = manager.getLaunchConfigurations(type);
			System.out.println(configurations);
		
		ILaunchConfigurationWorkingCopy configuration;
			configuration = type.newInstance(null, resource.getName());
	     	     
		return new ILaunchConfiguration[] {configuration};
		} catch (CoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return new ILaunchConfiguration[0];
	}

	@Override
	public ILaunchConfiguration[] getLaunchConfigurations(IEditorPart editorpart) {
		return null;
	}

	@Override
	public IResource getLaunchableResource(ISelection selection) {
		return (IResource) ((IStructuredSelection)selection).getFirstElement();
	}

	@Override
	public IResource getLaunchableResource(IEditorPart editorpart) {
		return null;
	}
	
	
	
	

}
