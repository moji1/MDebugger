/*******************************************************************************
 * Copyright (c) 2016 School of Computing -- Queen's University
 *
 * Description: no description currently
 * 
 * Contributors:
 *     Nicolas Hili <hili@cs.queensu.ca> - initial API and implementation
 ******************************************************************************/
package ca.queensu.cs.mdebugger.debugger.model;

import java.util.List;

import org.eclipse.core.resources.IMarkerDelta;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.debug.core.DebugEvent;
import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.DebugPlugin;
import org.eclipse.debug.core.IBreakpointListener;
import org.eclipse.debug.core.ILaunch;
import org.eclipse.debug.core.model.IBreakpoint;
import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.debug.core.model.IMemoryBlock;
import org.eclipse.debug.core.model.IProcess;
import org.eclipse.debug.core.model.IThread;
import org.eclipse.debug.ui.AbstractDebugView;
import org.eclipse.emf.common.ui.URIEditorInput;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.EObject;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.transaction.RecordingCommand;
import org.eclipse.emf.transaction.TransactionalEditingDomain;
import org.eclipse.gmf.runtime.notation.View;
import org.eclipse.jface.viewers.ISelection;
import org.eclipse.jface.viewers.StructuredSelection;
import org.eclipse.papyrus.editor.PapyrusMultiDiagramEditor;
import org.eclipse.papyrus.infra.core.sashwindows.di.service.IPageManager;
import org.eclipse.papyrus.infra.core.services.ServiceException;
import org.eclipse.papyrus.infra.core.services.ServicesRegistry;
import org.eclipse.swt.widgets.Display;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IEditorPart;
import org.eclipse.ui.ISelectionListener;
import org.eclipse.ui.IWorkbenchPart;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.PlatformUI;
import org.eclipse.uml2.uml.Model;
import org.eclipse.uml2.uml.NamedElement;
import org.eclipse.uml2.uml.Profile;
import org.eclipse.uml2.uml.StateMachine;
import org.eclipse.uml2.uml.Stereotype;
import org.eclipse.uml2.uml.Transition;

import ca.queensu.cs.mdebugger.debugger.breakpoints.MDebuggerBreakpoint;
import ca.queensu.cs.mdebugger.debugger.model.CapsuleThread.ElementKind;
import ca.queensu.cs.mdebugger.debugger.server.MDebuggerTCPServer;
import ca.queensu.cs.mdebugger.debugger.server.MDebuggerTCPSocket;
import ca.queensu.cs.mdebugger.debugger.server.MDebuggerTCPWriter;
import ca.queensu.cs.mdebugger.debugger.stackframes.CapsuleStackFrame;

/**
 * @author nicolas
 *
 */
public class MDebuggerDebugTarget extends MDebuggerDebugElement implements IDebugTarget, IBreakpointListener, ISelectionListener {

	private IProcess process;
    private ILaunch launch;

    private MDebuggerTCPServer tcpServerRunnable;
    private Thread tcpServer;
    
    private IThread[] threads;
    
    private MDebuggerTCPWriter writer;
    private MDebuggerTCPSocket reader;
    
    private Profile debuggingProfile;
    private TransactionalEditingDomain editingDomain;
    
    // The different states, which this IThread can have
    private enum State {
            RUNNING, STEPPING, SUSPENDED, TERMINATED
    }
    
    State currentState;
    
    private PapyrusMultiDiagramEditor editor;
	private String diPath;

    // the IProcess and ILaunch are provided by an IDebugTarget and therefore
    // they should be passed. The getProcess() and getLaunch() method should be
    // overridden accordingly. See DebugElement implementation
    public MDebuggerDebugTarget(IProcess process, ILaunch launch) {
            super(null);
            this.launch = launch;
            this.tcpServerRunnable = new  MDebuggerTCPServer(8001, this);
            this.tcpServer = new Thread(tcpServerRunnable);
            this.process = process;
            
            this.threads = new IThread[0];
            
            this.tcpServer.start();
            
    		diPath = "";
    		
    		try {
    			diPath = launch.getLaunchConfiguration().getAttribute("ca.queensu.cs.mdebugger.launcher.attributes.diPath", "/PingPong/model.di");
    		} catch (CoreException e) {
    			e.printStackTrace();
    		}
    		
    		Display.getDefault().syncExec(new PapyrusEditorUtil(this, diPath));
    		
    		// notify that this element has been created
            fireCreationEvent();
             
            // define the current state as running
            currentState = State.RUNNING;
             
    		 //System.out.println(this.editor);
    		 
/*    		 IEditorRegistry registry = PlatformUI.getWorkbench().getEditorRegistry();
    		 IEditorDescriptor[] desc = registry.getEditors("test.di");
    		 if (desc.length > 0) {
    			 IEditorDescriptor editor = desc[0];
    			 if ("org.eclipse.papyrus.infra.core.papyrusEditor".equals(editor.getId())) {    				 
    				 
    			 }
    		 } */
            final MDebuggerDebugTarget debugTarget = this;
            Display.getDefault().asyncExec(new Runnable() {
				
				@Override
				public void run() {
					PlatformUI.getWorkbench().getActiveWorkbenchWindow().getSelectionService().addSelectionListener(debugTarget);					
				}
			});
            //PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage().addSelectionListener(this);
    }

    // must be overridden since "this" cannot be passed in a constructor
    @Override
    public IDebugTarget getDebugTarget() {
            return this;
    }

    @Override
    public IProcess getProcess() {
            return this.process;
    }

    @Override
    public ILaunch getLaunch() {
            return launch;
    }

    @Override
    public boolean canTerminate() {
            return true;
    }

    @Override
    public boolean isTerminated() {
    	return State.TERMINATED.equals(currentState);
    }

    @Override
    public void terminate() throws DebugException {
    	

    	for (IThread thread: threads) {
    		thread.terminate();
    	}
    	
    	threads = new IThread[0];
    	tcpServerRunnable.close();
    	tcpServer.interrupt();
    	
    	fireTerminateEvent();
    	
    	currentState = State.TERMINATED;
    	final MDebuggerDebugTarget debugTarget = this;
        Display.getDefault().asyncExec(new Runnable() {
			
			@Override
			public void run() {
				/* Remove profile */
		    	URI uri = URI.createPlatformResourceURI(diPath, true);
		    	TransactionalEditingDomain editingDomain = (TransactionalEditingDomain) editor.getEditingDomain();
		    	ResourceSet resourceSet = editingDomain.getResourceSet();
		    	Resource profileResource = resourceSet.getResource(URI.createURI("platform:/plugin/ca.queensu.cs.mdebugger.profile/profile/debugging.profile.uml"), true);
		    	Profile debuggingProfile = (Profile) profileResource.getContents().get(0);
		    	Resource umlResource = resourceSet.getResource(uri, true);
		    	Model model = (Model) umlResource.getContents().get(0);
		    	editingDomain.getCommandStack().execute(new RecordingCommand(editingDomain) {
		    		
		    		@Override
		    		protected void doExecute() {
		    			if (model.isProfileApplied(debuggingProfile)) {
		    				model.unapplyProfile(debuggingProfile);
		    			/*	try {
								umlResource.save(null);
							} catch (IOException e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							} */
		    			}
		    		}
		    	});
				PlatformUI.getWorkbench().getActiveWorkbenchWindow().getSelectionService().removeSelectionListener(debugTarget);					
			}
		}); 
        
		
    }
    
    public void setWriter(MDebuggerTCPWriter writer) {
		this.writer = writer;
	}
    
    private void installDeferredBreakpoints() {
    	IBreakpoint[] breakpoints = DebugPlugin.getDefault().getBreakpointManager().getBreakpoints(getModelIdentifier());
    	DebugPlugin.getDefault().getBreakpointManager().addBreakpointListener(this);
	    for (int i = 0; i < breakpoints.length; i++) {
	    	breakpointAdded(breakpoints[i]);
	    }
	}

	public void setReader(MDebuggerTCPSocket reader) {
		this.reader = reader;
	}

    @Override
    public boolean canResume() {
    	return isSuspended();
    }

    @Override
    public boolean canSuspend() {
    	return State.RUNNING.equals(currentState);
    }

    @Override
    public boolean isSuspended() {
    	return State.SUSPENDED.equals(currentState);
    }

    @Override
    public void resume() throws DebugException {
            currentState = State.RUNNING;
            for (IThread thread: this.getThreads()) {
            	thread.resume();
            }
            
        	
        	if (this.writer != null)
        		this.writer.requestCapsuleList();
        	
            fireResumeEvent(DebugEvent.CLIENT_REQUEST);
    }

    @Override
    public void suspend() throws DebugException {
    	currentState = State.SUSPENDED;
    	fireSuspendEvent(DebugEvent.BREAKPOINT);
    }

    @Override
    public void breakpointAdded(IBreakpoint breakpoint) {
    	if (supportsBreakpoint(breakpoint)) {
    		try {
				if (breakpoint.isEnabled()) {
					MDebuggerBreakpoint bp = (MDebuggerBreakpoint)breakpoint;
					for (IThread thread: threads) {
						((CapsuleThread)thread).breakpointAdded(bp);
					}
				}
			} catch (CoreException e) {
				e.printStackTrace();
			}
    	}
    }

    @Override
    public void breakpointRemoved(IBreakpoint breakpoint, IMarkerDelta delta) {
    	if (supportsBreakpoint(breakpoint)) {
    		MDebuggerBreakpoint bp = (MDebuggerBreakpoint)breakpoint;
			for (IThread thread: threads) {
				((CapsuleThread)thread).breakpointRemoved(bp);
			}
    	}
    }

    @Override
    public void breakpointChanged(IBreakpoint breakpoint, IMarkerDelta delta) {
    	try {
			System.out.println(breakpoint.isEnabled());
		} catch (CoreException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    }

    @Override
    public boolean canDisconnect() {
            return false;
    }

    @Override
    public void disconnect() throws DebugException {
    }

    @Override
    public boolean isDisconnected() {
            return false;
    }

    @Override
    public boolean supportsStorageRetrieval() {
            return false;
    }

    @Override
    public IMemoryBlock getMemoryBlock(long startAddress, long length) throws DebugException {
            return null;
    }

    @Override
    public IThread[] getThreads() throws DebugException {
            if (isTerminated()) {
                    return new IThread[0];
            }
            return this.threads;
    }
    
    public IThread getThread(String name) {
    	try {
	    	IThread[] threads = getThreads();
	    	for (int i = 0; i < threads.length; i++) {
	    		CapsuleThread thread = (CapsuleThread)threads[i];
					if (thread != null && thread.getCapsuleName().equals(name))
						return thread;
	    	}
    	} catch (DebugException e) {
    		// TODO Auto-generated catch block
    		e.printStackTrace();
    	}
    	return null;
    }

    @Override
    public boolean hasThreads() throws DebugException {
            return (this.threads != null && this.threads.length > 0);
    }

    @Override
    public String getName() throws DebugException {
            return "Debug target";
    }

    @Override
    public boolean supportsBreakpoint(IBreakpoint breakpoint) {
    		return (breakpoint.getModelIdentifier().equals(getModelIdentifier()));
    }

    public void dispose() {
    	DebugPlugin.getDefault().getBreakpointManager().removeBreakpointListener(this);
        fireTerminateEvent();
    }

	public void setCapsule(String[] capsules, String[] currentStates) {
		int n = capsules.length;
		IThread[] threads = new IThread[n];
		
		for (int i = 0; i < n; i++) {
			
			CapsuleThread capsuleThread = new CapsuleThread(this, capsules[i]);
			capsuleThread.setCurrentState(currentStates[i]);
			threads[i] = capsuleThread;
		}
		this.threads = threads;
		installDeferredBreakpoints();
	}
	
	public void modifyValue(String capsuleName, String variableName, String value) {
		this.writer.modifyValue(capsuleName, variableName, value);
	}

	public void stepOver(String capsuleName) {
		this.writer.stepOver(capsuleName);
	}
	

	public void refreshCapsule(String capsuleName) {
		this.writer.requestEventList(capsuleName, 5);
	}
	
	public class PapyrusEditorUtil implements Runnable {

		private MDebuggerDebugTarget target;
		private String path;

		public PapyrusEditorUtil(MDebuggerDebugTarget target, String path) {
			this.target = target;
			this.path = path;
		}
		
		@Override
		public void run() {
			try {
				URI uri = URI.createPlatformResourceURI(path, true);
				IEditorInput editorInput = new URIEditorInput(uri);
				IEditorPart papyrusEditor = PlatformUI.getWorkbench().getActiveWorkbenchWindow().getActivePage().openEditor(editorInput, "org.eclipse.papyrus.infra.core.papyrusEditor");
				this.target.editor = (PapyrusMultiDiagramEditor)papyrusEditor;
				
				/* Add profile */
				editingDomain = (TransactionalEditingDomain) this.target.editor.getEditingDomain();
				ResourceSet resourceSet = editingDomain.getResourceSet();
				Resource profileResource = resourceSet.getResource(URI.createURI("platform:/plugin/ca.queensu.cs.mdebugger.profile/profile/debugging.profile.uml"), true);
				debuggingProfile = (Profile) profileResource.getContents().get(0);
				Resource umlResource = resourceSet.getResource(uri, true);
				Model model = (Model) umlResource.getContents().get(0);
				editingDomain.getCommandStack().execute(new RecordingCommand(editingDomain) {
					
					@Override
					protected void doExecute() {						
						model.applyProfile(debuggingProfile);
						/*org.eclipse.uml2.uml.Class counter = (Class) model.getPackagedElement("Counter");
						StateMachine fsm = (StateMachine) counter.getOwnedBehaviors().get(0);
						org.eclipse.uml2.uml.State state = (org.eclipse.uml2.uml.State) fsm.getRegions().get(0).getSubvertex("COUNTING");
						System.out.println(state);
						state.applyStereotype((Stereotype) debuggingProfile.getPackagedElement("Current"));
						*//*try {
							umlResource.save(null);
						} catch (IOException e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}*/
					}
				});
				
			} catch (PartInitException e) {
				e.printStackTrace();
			}
		}
		
	}

	public void requestEventList(String capsuleName, int i) {
		this.writer.requestEventList(capsuleName, i);
	}

	public void resumeCapsule(String capsuleName) {
		this.writer.resumeCapsule(capsuleName);
	}

	public void addBreakpoint(MDebuggerBreakpoint breakpoint, String capsuleName) {
		this.writer.toggleBreakpoint(breakpoint, capsuleName, false);
	}
	
	public void removeBreakpoint(MDebuggerBreakpoint breakpoint, String capsuleName) {
		this.writer.toggleBreakpoint(breakpoint, capsuleName, true);
	}

	@Override
	public void selectionChanged(IWorkbenchPart part, ISelection selection) {
		if (part instanceof AbstractDebugView) {
			Object element = ((StructuredSelection)selection).getFirstElement();
			if (element instanceof CapsuleThread) {
				CapsuleThread thread = (CapsuleThread)element;
				View view = revealDiagram(thread);
				
			}
			else if (element instanceof CapsuleStackFrame) {
				
				CapsuleThread thread = (CapsuleThread) ((CapsuleStackFrame)element).getThread();
				View view = revealDiagram(thread);
			}
		}
	}
	
	private View revealDiagram(CapsuleThread thread) {
		String capsuleName = thread.getCapsuleClassName();
		
		ServicesRegistry serviceRegistry = (ServicesRegistry)editor.getAdapter(ServicesRegistry.class);
		try {
			IPageManager pageManager = serviceRegistry.getService(IPageManager.class);
			List<Object> pages = pageManager.allPages();
			for (Object page: pages) {
				if (page instanceof View) {
					
					EObject eobj = ((View)page).getElement();
					if (eobj instanceof StateMachine) {
						StateMachine fsm = (StateMachine)eobj;
						displayCurrentState(fsm, thread.currentElementKind, thread.currentElementName);
						if(fsm.getContext().getName().equalsIgnoreCase(capsuleName)) {
							
							if (!pageManager.isOpen(page))
								pageManager.openPage(page);
							pageManager.selectPage(page);
							return (View) page;
						}
					}
				}
			}
		} catch (ServiceException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return null;
	}
	
	private NamedElement oldElement = null;
	
	private void displayCurrentState(StateMachine fsm, ElementKind currentElementKind, String currentState) {
		final NamedElement element = (currentElementKind.equals(ElementKind.STATE)) ?
				fsm.getRegions().get(0).getSubvertex(currentState) :
				fsm.getRegions().get(0).getTransition(currentState)
		;
				
		
		if (element != null) {
			
			if (element == oldElement) {
				return;
			}
			
			editingDomain.getCommandStack().execute(new RecordingCommand(editingDomain) {

				@Override
				protected void doExecute() {
					Stereotype current = (Stereotype) debuggingProfile.getPackagedElement("Current");
					
					if(oldElement != null && oldElement.isStereotypeApplied(current))
						oldElement.unapplyStereotype(current);
						
					if(!element.isStereotypeApplied(current))
						element.applyStereotype(current);
					
					oldElement = element;
				}
			});
		}
	}


}
