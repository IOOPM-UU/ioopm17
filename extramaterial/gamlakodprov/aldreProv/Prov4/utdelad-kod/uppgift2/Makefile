main:	everything

# java settings
JAVA_COMPILER   = javac
JAVA_OPTIONS    = -d . -classpath . 

mm/MemoryManager.class:
	$(JAVA_COMPILER) $(JAVA_OPTIONS) MemoryManager.java

mm/Chunk.class:
	$(JAVA_COMPILER) $(JAVA_OPTIONS) Chunk.java

mm/MemoryFullException.class:
	$(JAVA_COMPILER) $(JAVA_OPTIONS) MemoryFullException.java

Driver.class:
	$(JAVA_COMPILER) $(JAVA_OPTIONS) Driver.java

everything: mm/MemoryFullException.class mm/Chunk.class mm/MemoryManager.class Driver.class

clean:
	rm -f mm/*.class Driver.class

