class SimulinkPlant:
    def __init__(self,modelName = None):
        
        self.modelName = modelName #The name of the Simulink Model (To be placed in the same directory as the Python Code) 
        #Logging the variables
        self.yHist = 0 
        self.tHist = 0 
        
    def setControlAction(self,u):
        #Helper Function to set value of control action
        self.eng.set_param('{}/u'.format(self.modelName),'value',str(u),nargout=0)
    
    def getHistory(self):
        #Helper Function to get Plant Output and Time History
        return self.eng.workspace['output'],self.eng.workspace['tout']
        
    def connectToMatlab(self):
        
        print("Starting matlab")
        self.eng = matlab.engine.start_matlab()
        
        print("Connected to Matlab")
        
        #Load the model
        self.eng.eval("model = '{}'".format(self.modelName),nargout=0)
        self.eng.eval("load_system(model)",nargout=0)
        
        #Initialize Control Action to 0
        self.setControlAction(0)
        print("Initialized Model")
        
        #Start Simulation and then Instantly pause
        self.eng.set_param(self.modelName,'SimulationCommand','start','SimulationCommand','pause',nargout=0)
        self.yHist,self.tHist = self.getHistory()
    
    def connectController(self,controller):
        self.controller = controller
        self.controller.initialize()
    
    def simulate(self):
        # Control Loop
        while(self.eng.get_param(self.modelName,'SimulationStatus') != ('stopped' or 'terminating')):
            
            #Generate the Control action based on the past outputs
            u = self.controller.getControlEffort(self.yHist,self.tHist)
            
            #Set that Control Action
            self.setControlAction(u)
            
            #Pause the Simulation for each timestep
            self.eng.set_param(self.modelName,'SimulationCommand','continue','SimulationCommand','pause',nargout=0)
            
            self.yHist,self.tHist = self.getHistory()
        
    def disconnect(self):
        self.eng.set_param(self.modelName,'SimulationCommand','stop',nargout=0)
        self.eng.quit()
