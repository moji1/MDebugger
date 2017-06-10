package ca.queensu.cs.mdebugger.debugger.server;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.HashMap;
import java.util.Map;

import org.eclipse.debug.core.DebugException;
import org.eclipse.debug.core.ILaunch;
import org.eclipse.debug.core.model.IDebugTarget;
import org.eclipse.debug.core.model.IStackFrame;
import org.eclipse.debug.core.model.IThread;
import org.eclipse.debug.core.model.IVariable;
import org.eclipse.ui.internal.commands.CommandService;

import ca.queensu.cs.mdebugger.debugger.model.CapsuleThread;
import ca.queensu.cs.mdebugger.debugger.model.MDebuggerDebugTarget;
import ca.queensu.cs.mdebugger.debugger.stackframes.CapsuleStackFrame;
import ca.queensu.cs.mdebugger.debugger.variables.MDebuggerVariable;

public class MDebuggerTCPSocket extends Thread {
	
	protected Socket socket;
	private IDebugTarget target;
	
	public static enum Command {
		WAITING_FOR_BREAKPOINT_REACHED,
		WAITING_FOR_BREAKPOINT_LIST,
		WAITING_FOR_EVENT_LIST,
		WAITING_FOR_VALUE_CHANGE_ACK,
		WAITING_FOR_ACK,
		WAITING_FOR_LAST_EVENT,
		STEPPING,
		RESUME
	};
	
	private Map<Integer, Command> commandStack;
	
	public State currentState;

	public MDebuggerTCPSocket(Socket clientSocket, IDebugTarget target) {
		this.socket = clientSocket;
		this.commandStack = new HashMap<Integer, Command>();
		this.target = target;
	}
	
	@Override
	public void interrupt() {
		super.interrupt();
	}
	
	public void run() {
    	
        InputStream inp = null;
        BufferedReader brinp = null;
        DataOutputStream out = null;
        try {
            inp = socket.getInputStream();
            brinp = new BufferedReader(new InputStreamReader(inp));
            out = new DataOutputStream(socket.getOutputStream());
        } catch (IOException e) {
            return;
        }
        
        char[] sizeBuffer = new char[4];
        char[] messageBuffer;
        String message;
        int size;
        
        while (true) {
            try {
            	
            	int result = brinp.read(sizeBuffer, 0, 4);
            	if (result == -1)
            		break;

            	size = Integer.parseInt(new String(sizeBuffer));
            	
            	messageBuffer = new char[size];
            	
            	brinp.read(messageBuffer, 0, size);
            	
            	message = new String(messageBuffer);
            	            	
            	int id = 0;
            	
            	
            	String[] table = message.split("[|]", 2);
            	String messageId = table[0];
            	message = table[1];
            	
            	try{
            		id = Integer.parseInt(messageId);
            	} catch (NumberFormatException e) {
            	}
            	
            	System.out.println("Command id:" + id);

            	if (id == 0) {
            		this.retrieveCapsuleList(message);
            	}
            	else {
            	
	            	Command command = this.commandStack.get(id);
	            	
	            	if (command == null)
	            		return;
	            	
	            	switch (command) {
	            	case WAITING_FOR_BREAKPOINT_REACHED:
	        			this.retrieveCapsuleList(message);
	        		break;
	            	case WAITING_FOR_EVENT_LIST:
	        			this.retrieveEventList(message);
	        			break;
	            	case STEPPING:
	            	//	this.refreshAfterACK(message);
	            		break;
	            	case WAITING_FOR_LAST_EVENT:
	            		System.err.println("never called");
	        			this.retrieveLastEvent(message);
	        			break;
	            	case WAITING_FOR_VALUE_CHANGE_ACK:
	            		this.refreshAfterACK(message);
	            		break;
	            	case WAITING_FOR_ACK:
	        		break;
	            	}
	            	
	            	if (id != 0)
	            		commandStack.remove(id);
            	}
            	
            	sizeBuffer = new char[4];
            	messageBuffer = null;
            	
            } catch (IOException e) {
                e.printStackTrace();
                return;
            } catch (DebugException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
        }
        
        System.out.println("Deleting client");
    }
	
	private void retrieveEventList(String message) {

		String[] traces = message.split("[|]");
		
		if (traces.length <= 1)
			return;
		
		String capsule = traces[0];
		String currentState = traces[1];
		IThread thread = ((MDebuggerDebugTarget)this.target).getThread(capsule);
		
		IStackFrame[] stackFrames;
		IVariable[] variables;
		
		String[] events = new String[traces.length -2];
		for (int i = 0; i < events.length; i++) {
			events[i] = traces[i+2];
		}
		
		((CapsuleThread)thread).setEvents(events);
		
	}
	
	private void retrieveLastEvent(String message) {

		String[] traces = message.split("[|]");
		String capsule = traces[0];
		String currentState = traces[1];
		//String event = traces[2];
		
		IThread thread = ((MDebuggerDebugTarget)this.target).getThread(capsule);
		
//		String[] events = new String[traces.length -2];
		for (int i = 0; i < traces.length -2; i++) {
			String event = traces[i+2];
			((CapsuleThread)thread).pushEvent(event);
		}	
		
	}
	
	private void refreshAfterACK(String message) {

		String[] traces = message.split("[|]");
		String capsule = traces[1];

		((MDebuggerDebugTarget)target).refreshCapsule(capsule);
	}
	
	public Map<Integer, Command> getCommandStack() {
		return this.commandStack;
	}

	public void retrieveCapsuleList(String message) throws DebugException {
		
        String[] capsuleTraces;
        
		capsuleTraces = message.split("&");

    	int n = capsuleTraces.length;
    	String[] capsules = new String[n];
    	String[] currentStates = new String[n];
    	
    	for (int i = 0 ; i < n; i++) {
    		String[] traces = capsuleTraces[i].split("[|]");
    		capsules[i] = traces[0];
    		currentStates[i] = traces[1];
    	}
    	    	
    	((MDebuggerDebugTarget)target).setCapsule(capsules, currentStates);
    	
    	if (target.canSuspend())
    		target.suspend();
    	
	}

}
