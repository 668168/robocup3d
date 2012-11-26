#
# this is the init script of the Zeitgeist library
# 

# here we perform the callback to zeitgeist
def method_missing(methId, *args)
	str = methId.id2name
	selectCall str, args
end

# this method allows us to create new instance variables in class objects
# we use class objects as 'namespaces'
# createVariable can be used in two forms:
# - 2 parameters: createVariable("myNamespace.myVarName", "myValue");
# - 3 parameters: createVariable("myNamespace", "myVarName", "myValue");
def createVariable (namespace, variable, value = nil)
        # 2 parameters means the "namespace.variable", "value" form
        if (value == nil)
	        value = variable;
	        # parse namespace into a namespace and varName pair
	        periodIndex = namespace.index('.');
                if (periodIndex != nil && periodIndex > 0)
                        variable = namespace[(periodIndex+1)..-1];
                        namespace = namespace[0..(periodIndex-1)];
		else
		        namespace = nil;
		end
	end  
        # here we have 3 parameters: namespace, variable, and value   
        if (namespace != nil)
                eval <<-EOS
                        class #{namespace}
                        end
                        class << #{namespace}
                                attr_accessor :#{variable}
                        end
                        #{namespace}.#{variable} = value
                EOS
        end
end

# this is a proxy class for objects created with 'create' via the Zeitgeist
# framework. It allows arbitrary methods to be called on the object and allows
# for much nicer syntax, than the select-call paradigm
class ZeitgeistObject
	# a pointer to the object represented by t
	attr_reader :objPointer

	def method_missing(methId, *args)
		#print "Missing method", @objPointer, "->", methId.id2name, "\n"
		str = methId.id2name
		thisCall @objPointer, str, args
	end

	def initialize(objPointer)
		#print "Creating new ZeitgeistObject ", objPointer, "\n"
		@objPointer = objPointer
	end
end

# set up some useful aliases
alias cd selectObject

