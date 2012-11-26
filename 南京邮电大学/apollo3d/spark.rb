#
# spark.rb, setup kerosin application framework
#

#
# define constants used to setup spark
#

# scene and server path
$scenePath = '/usr/scene/'
$serverPath = '/sys/server/'

# (Inputsystem)
#

# the default InputSystem used to read keyboard, mouse and timer input
$defaultInputSystem = 'InputSystemSDL'

# the name of the default bundle that contains the default InputSystem
$defaultInputSystemBundle = 'inputsdl'

# (OpenGL rendering)
#

# the default OpenGLSystem used for rendering
$defaultOpenGLSystem = 'OpenGLSystemSDL'

# the name of the bundle that contains the default OpenGLSystem
$defaultOpenGLBundle = 'openglsyssdl'

#
# (AgentControl) constants
#
$agentStep = 0.02
$agentType = 'tcp'
$agentPort = 3100

# (MonitorControl) constants
#

# define the monitor update interval in cycles
$renderStep = 0.04
$monitorLoggerStep = 0.2;
$monitorStep = 0.04
$serverType = 'tcp'
$serverPort = 3200

# (SparkMonitorClient) constants
#
$monitorServer = '127.0.0.1'
$monitorPort = 3200
# socket type ('tcp' or 'udp')
$monitorType = 'tcp'

# (Global Physics / World) constants
#
$physicsGlobalCFM = 0.00001
$physicsGlobalGravity = -9.81

#
# below is a set of utility functions for the user app
#

# return the existing instance or create a new one
def sparkGetOrCreate(className, path)
  obj = get(path)

  if (obj != nil)
    return obj
  end

  #print "(spark.rb) creating "
  #print className
  #print " instance at "
  #print path
  #print "\n"

  return new(className, path)
end

# delete any existing instance and create a new one
def sparkCreate(className, path)
  delete(path)

  #print "(spark.rb) creating "
  #print className
  #print " instance at "
  #print path
  #print "\n"

  return new(className, path)
end

def sparkGetMonitorServer
  return sparkGetOrCreate('oxygen/MonitorServer', $serverPath+'monitor')
end

def sparkGetPhysicsServer
  return sparkGetOrCreate('oxygen/PhysicsServer', $serverPath+'physics')
end

def sparkGetSceneServer
  return sparkGetOrCreate('oxygen/SceneServer', $serverPath+'scene')
end

def sparkGetGameControlServer
  return sparkGetOrCreate('oxygen/GameControlServer', $serverPath+'gamecontrol')
end

def sparkGetSimulationServer
  return sparkGetOrCreate('oxygen/SimulationServer', $serverPath+'simulation')
end

def sparkGetGeometryServer
  return sparkGetOrCreate('oxygen/GeometryServer', $serverPath+'geometry')
end

def sparkGetMaterialServer
  return sparkGetOrCreate('kerosin/MaterialServer', $serverPath+'material')
end

def sparkGetOpenGLServer
  return sparkGetOrCreate('kerosin/OpenGLServer', $serverPath+'opengl')
end

def sparkGetInputServer
  return sparkGetOrCreate('kerosin/InputServer', $serverPath+'input')
end

def sparkGetFontServer
  return sparkGetOrCreate('kerosin/FontServer', $serverPath+'font')
end

def sparkGetRenderServer
  return sparkGetOrCreate('kerosin/RenderServer', $serverPath+'render')
end

def sparkGetImageServer
  return sparkGetOrCreate('kerosin/ImageServer', $serverPath+'image')
end

def sparkGetTextureServer
  return sparkGetOrCreate('kerosin/TextureServer', $serverPath+'texture')
end


# rebuild scene and update all cached references
def sparkResetScene
  scene = get($scenePath)
  if (scene != nil)
    scene.unlinkChildren()
  end

  # (re-)create world and space aspects
  world = new('oxygen/World', $scenePath+'world')
  world.setGravity(0.0, 0.0, $physicsGlobalGravity)
  world.setCFM($physicsGlobalCFM)
  world.setAutoDisableFlag(true)             #not in simspark
  world.setContactSurfaceLayer(0.001)	     #not in simspark

  new('oxygen/Space', $scenePath+'space')

  # invalidate all cached references
  scriptServer = get($serverPath+'script')
  if (scriptServer != nil)
    scriptServer.updateCachedAllNodes()
  end

  # force update references to scene objects (world, space etc.)
  sceneServer = sparkGetSceneServer()
  if (sceneServer != nil)
    sceneServer.setActiveScene($scenePath)
  end

  # reset material definitions
#   materialServer = sparkGetMaterialServer()
#   materialServer.resetMaterials()

  # reset simulation time
  simulationServer = sparkGetSimulationServer()
  if (simulationServer != nil)
    simulationServer.resetTime()
  end
end

def sparkSetupMonitor
  print "(spark.rb) sparkSetupMonitor\n"

  # add the agent control node
  simulationServer = sparkGetSimulationServer()
  if (simulationServer != nil)
    simulationServer.setMultiThreads(false)
  end

  monitorClient = sparkCreate('SparkMonitorClient', $serverPath+'simulation/SparkMonitorClient')
  monitorClient.setServer($monitorServer)
  monitorClient.setPort($monitorPort)

  if ($monitorType == 'udp')
    monitorClient.setClientTypeUDP()
  else if ($monitorType == 'tcp')
	 monitorClient.setClientTypeTCP()
       else
	 print "(spark.rb) unknown monitor socket type "
	 print $monitorType
	 print "\n"
       end
  end

  rubySceneImporter = get($serverPath+'scene/RubySceneImporter')
  if (rubySceneImporter != nil)
    rubySceneImporter.setUnlinkOnCompleteScenes(true);
  end
end

def sparkSetupMonitorLogPlayer
  print "(spark.rb) sparkSetupMonitorLogPlayer\n"

  simulationServer = sparkGetSimulationServer()
  if (simulationServer != nil)
    simulationServer.setMultiThreads(false)

    monitorClient = sparkCreate('SparkMonitorLogFileServer', $serverPath+'simulation/SparkMonitorLogFileServer')

    monitorClient.setFileName($logPlayerFile)
    monitorClient.setStepDelay(33000)
  end

  rubySceneImporter = get($serverPath+'scene/RubySceneImporter')
  if (rubySceneImporter != nil)
    rubySceneImporter.setUnlinkOnCompleteScenes(true);
  end
end

#
# install a class below the SparkMonitorClient that implementes the
# simulation specific monitor processing
#
def sparkRegisterCustomMonitor(className)
  print "(spark.rb) sparkRegisterCustomMonitor " + className + "\n"
  sparkGetSimulationServer()
  sparkCreate(className, $serverPath+'simulation/SparkMonitorClient/'+className)
end

#
# install a class below the Spark RenderControl node that implements
# application specific render logic
#
def sparkRegisterCustomRender(className)
  print "(spark.rb) sparkRegisterCustomRender " + className + "\n"
  sparkGetSimulationServer()
  sparkCreate(className, $serverPath+'simulation/RenderControl/'+className)
end

#
# install a class below the Spark InputControl node that implements
# application specific input processing
#
def sparkRegisterCustomInput(className)
  print "(spark.rb) sparkRegisterCustomInput " + className + "\n"
  sparkGetSimulationServer()
  sparkCreate(className, $serverPath+'simulation/InputControl/'+className)
end

#
# install a class below the Spark MonitorSystem node that parses
# commands received from a monitor client
#
def sparkRegisterMonitorCmdParser(className)
  print "(spark.rb) sparkRegisterMonitorCmdParser " + className + "\n"
  sparkGetMonitorServer()
  sparkCreate(className, $serverPath+'monitor/SparkMonitor/'+className)
end

def sparkSetupServer
  print "(spark.rb) sparkSetupServer\n"

  # add the agent control node
  simulationServer = sparkGetSimulationServer()

  if (simulationServer != nil)
    simulationServer.setMultiThreads(false);
    simulationServer.initControlNode('oxygen/AgentControl','AgentControl')

    # set auto speed adjust mode.
    # a smaller value for MaxStepsPerCycle is recommended specially for slow systems
    simulationServer.setAdjustSpeed(true)
    simulationServer.setMaxStepsPerCyle(3)
  end

  # set port and socket type for agent control
  agentControl = get($serverPath+'simulation/AgentControl');

  if (agentControl != nil)
    agentControl.setServerPort($agentPort)
    agentControl.setStep($agentStep)
  end

  if ($agentType == 'udp')
	agentControl.setServerTypeUDP()
  else if ($agentType == 'tcp')
	agentControl.setServerTypeTCP()
       else
	 print "(spark.rb) unknown agent socket type "
	 print $agentType
	 print "\n"
       end
  end

  monitorControl = sparkCreate('oxygen/MonitorControl',$serverPath+'simulation/MonitorControl')
  monitorControl.setStep($monitorStep)
  monitorControl.setServerPort($serverPort)

  if ($serverType == 'udp')
    monitorControl.setServerTypeUDP()
  else if ($serverType == 'tcp')
	 monitorControl.setServerTypeTCP()
       else
	 print "(spark.rb) unknown monitor socket type "
	 print $serverType
	 print "\n"
       end
  end

  #
  # log recording setup

  if ($recordLogfile == true)
    print "(spark.rb) recording Logfile as 'sparkmonitor.log'\n"
    monitorLogger = sparkCreate('oxygen/MonitorLogger', $serverPath+'simulation/MonitorLogger')
    monitorLogger.setStep($monitorLoggerStep)
  end
end

def sparkSetupRendering(openGLSystem = $defaultOpenGLSystem)
  print "(spark.rb) sparkSetupRendering\n"
  print "(spark.rb) using OpenGLSystem '" + openGLSystem + "'\n"

  #
  # setup the kerosin render framework

  openGLServer = sparkGetOpenGLServer()

  if (openGLSystem == $defaultOpenGLSystem)
    importBundle($defaultOpenGLBundle)
  end

  openGLServer.init(openGLSystem)

  sparkGetRenderServer()
  sparkGetImageServer()
  sparkGetTextureServer()

  #
  # setup the InputServer

  # create the InputServer and use a german keyboard layout
  inputServer = sparkGetInputServer()
  inputServer.setScanCodeMapping('german.scan.rb');

  # setup the FontServer
  sparkGetFontServer()

  #
  # register render control node to the simulation server
  simulationServer = sparkGetSimulationServer()

  if (simulationServer != nil)
    simulationServer.initControlNode('kerosin/RenderControl','RenderControl')
  end

  renderControl = get($serverPath+'simulation/RenderControl')
  if (renderControl != nil)
    renderControl.setStep($renderStep)
  end
end

def sparkSetupInput(inputSystem = $defaultInputSystem)
  print "(spark.rb) sparkSetupInput\n"
  print "(spark.rb) using InputSystem '" + inputSystem + "'\n"

  # setup the SDL input system
  if (inputSystem == $defaultInputSystem)
    importBundle($defaultInputSystemBundle)
  end

  inputServer = sparkGetInputServer()
  if (inputServer != nil)
    inputServer.init(inputSystem)

    # add devices
    inputServer.createDevice('Timer')
    inputServer.createDevice('Keyboard')
    inputServer.createDevice('Mouse')
  end

  #
  # register input control node to the simulation server

  simulationServer = sparkGetSimulationServer()
  if (simulationServer != nil)
    # add the input control node
    simulationServer.initControlNode('kerosin/InputControl','InputControl')
  end
end

def sparkSetupTrain()
  print "(spark.rb) sparkSetupTrain\n"
  #
  # register train control node to the simulation server

  simulationServer = sparkGetSimulationServer()
  if (simulationServer != nil)
    # add the train control node
    simulationServer.initControlNode('oxygen/TrainControl','TrainControl')
  end
end

# add a camera with an FPS Controller to the scene at path
def sparkAddFPSCamera(
		      path,
		      x = 0.0, y = 0.0, z = 4,
		      vAngle = 45.0,
                      hAngle = 10.0,
		      maxSpeed = 15.0,
		      accel = 40.0,
		      drag = 4,
		      addCollider = false,
		      colliderRadius = 2.0,
                      znear = 0.1
		      )

  print "(spark.rb) sparkAddFPSCamera at " + path + "\n"

  # add a camera. The camera movement is controlled using an
  # FPSController.
  cameraTransform = sparkCreate('oxygen/Transform',path)
  cameraTransform.setLocalPos(x,y,z)
  camera = new('oxygen/Camera',path+'/camera')
  camera.setZNear(znear)

  # the camera is not affected by gravity but restricted to a maximum
  # speed
  body = new('oxygen/Body',path+'/physics')
  body.useGravity(false);
  velCtr = new('oxygen/VelocityController',path+'/physics/velctr')
  velCtr.setMaxVelocity(maxSpeed)

  # add an FPSController to move the camera and set the applied
  # acceleration
  fpsController = new('oxygen/FPSController',path+'/physics/controller')
  fpsController.setAcceleration(accel)
  fpsController.setVAngle(vAngle)
  fpsController.setHAngle(hAngle)

  inputControl = get($serverPath+'simulation/InputControl')
  if (inputControl != nil)
    inputControl.setFPSController(path+'/physics/controller')
  end

  # add an DragController to work against the camera acceleration
  dragController = new('oxygen/DragController',path+'/physics/drag')
  dragController.setLinearDrag(drag)

  if addCollider
    # add an Collider that allows the camera to push objects
    collider = new('oxygen/SphereCollider', path+'/geometry')
    collider.setRadius(colliderRadius)

    handler = new('oxygen/ContactJointHandler', path+'geometry/contact')
    handler.setContactBounceMode true
    handler.setMinBounceVel 2
  end
end

#
# registers a new logTarget to the LogServer
#
# valid logTarget value are ':cout' and ':cerr' for stdout and stderr
# output, as well as any other file name, e.g. 'log.txt'
#
# logType denotes the debug to be attached to the
# logtarget. Valid streams are 'eNone', 'eDebug' and 'eWarning'
#
def sparkEnableLog(logTarget, logType)
  print "(spark.rb) sparkEnableLog logTarget="+logTarget+" logType="+logType+"\n"

  logServer = get($serverPath+'log')
  if (logServer != nil)
    logServer.addStream(logTarget, logType)
  end
end

# deregisters all output stream
def sparkResetLogging()
  print "(spark.rb) sparkResetLogging removing all log targets\n";

  logServer = get($serverPath+'log')
  if (logServer != nil)
    logServer.removeAllStreams()
  end
end

# logs all error output to cerr
def sparkLogErrorToCerr()
  sparkEnableLog(':cerr', 'eError')
end

# logs all debug output to cerr
def sparkLogDebugToCerr()
  sparkEnableLog(':cerr', 'eDebug')
end

# logs all output to cerr
def sparkLogAllToCerr()
  sparkEnableLog(':cerr', 'eAll')
end

# logs all error output to 'fileName'
def sparkLogErrorToFile(fileName)
  sparkEnableLog(fileName, 'eError')
end

# logs all debug output to 'fileName'
def sparkLogDebugToFile(fileName)
  sparkEnableLog(fileName, 'eDebug')
end

# logs all output to 'fileName'
def sparkLogAllToFile(fileName)
  sparkEnableLog(fileName, 'eAll')
end

# register an integrated agent
def addIntegratedAgent(agentType, number)
  sparkGetOrCreate(agentType, "/usr/agent/behavior#{number}")
end

#
# setup spark
#

#print "(spark.rb) setup\n"

#
# set up logging
#logServer = get($serverPath+'log')

#if (logServer != nil)
#  logServer.addStream(':cerr', 'eError')
#end

sparkResetLogging()

#
# setup the PhysicsServer
sparkGetPhysicsServer()

#
# setup the SceneServer
sceneServer = sparkGetSceneServer()
sceneServer.createScene($scenePath)

#
# setup the GeometryServer
# importBundle 'voidmeshimporter'
# importBundle 'objimporter'

# geometryServer = sparkGetGeometryServer()
# geometryServer.initMeshImporter("VoidMeshImporter");
# geometryServer.initMeshImporter("ObjImporter");

# use the ruby scene importer to import scenes
# importBundle 'rubysceneimporter'
sceneServer.initSceneImporter("RubySceneImporter");

# use the ros scene importer to import scenes
# importBundle 'rosimporter'
# sceneServer.initSceneImporter("RosImporter");

#
# setup the MaterialServer
# sparkGetMaterialServer()

#
# setup the MonitorServer
# monitorServer = sparkGetMonitorServer()

# register the SparkMonitor system
# importBundle 'sparkmonitor'
# monitorServer.registerMonitorSystem('SparkMonitor')

#
# setup the GameControlServer
gameControlServer = sparkGetGameControlServer()

# register the s-expression parser to the GameControlServer
# importBundle "sexpparser"
gameControlServer.initParser('SexpParser')

# register the SceneEffector to the GameControlServer
# importBundle "sceneeffector"
# gameControlServer.initEffector('SceneEffector')

# prepare scene
sparkResetScene()

#
# import the spark perceptors and effector set
# importBundle "sparkagent"

#
# importBundle "gyrorateperceptor"

#
# importBundle "collisionperceptor"
