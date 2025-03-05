# Class #1—Introduction to Computer Organization

>This file will contain information about the first module of week one on computer organization. 
> The contents given in this week's class were all related to computer components, computer 
> organization, and computer architecture. 

## Why Study Computer Organization and Architecture?
Computer architecture is regarded as one core subject in a computer science career, although we 
are technically defined as an engineering degree, our accreditations require us to follow this.

<p>Independently of our accreditations, understanding both computer organization and 
architecture has its own benefits. For example, it can allow us to make <code>informed 
optimizations, make best use of our software tools, and computer languages</code>. Additionally, 
understand how our computer is organized within, and how these layers are architected on top, 
gives us a broad overview and knowledge of <code>a system's functional components, 
perforamnce and interactions</code>
<br/><br/>
In general, our parent organizations say
</p>
<procedure>
<i>" So long as we are related to software and hardware, it is imperative that we know how it 
works internally, to make best use of our tools, and understand the way our hardware works and 
interacts with our code."</i>
</procedure>
<p>
Some important points we have to understand about computer organization are
</p>
<procedure title="Computer Organization | Objectives" collapsible="true">
<list>
<li><b><format color="CornFlowerBlue">Trade-offs</format></b>: understand the complexity of the 
trade=offs between CPU clock speed, cache size, bus organization, core number, etc.</li>
<li><b><format color="CornFlowerBlue">Underlying architecture</format></b>: understanding the 
architecture of our systems to implement optimum solutions</li>
</list>
</procedure>

## Organization and Architecture

### What is Computer Architecture
<p>When we talk about this topic, we are mostly oriented to the <code>firmware</code>, that is 
stored within a computer system. It can be defined as <code>the code that runs and 
organizes the internals of our computers</code>.
<br/><br/>
Our computers have some important areas that are related to this topic
</p>
<procedure title="Example Topics Related to Computer Architecture" collapsible="true">
<list columns="1">
<li><b><format color="CornFlowerBlue">Instruction Set of our Machine</format></b>: 
<p>The complete 
set of instructions that a processor can execute. This includes:</p>
 <list>
<li><b><format color="Orange">Arithmetic operations</format></b>:

- ADD: Addition operation
- SUB: Subtraction operation
- MUL: Multiplication operation
- DIV: Division operation
</li>
<li><b><format color="Orange">Data movement</format></b>:

- LOAD: Transfers data from memory to register
- STORE: Transfers data from register to memory
- MOV: Moves data between registers
</li>
<li><b><format color="Orange">Control flow</format></b>:

- JUMP: Unconditional transfer of control
- BRANCH: Conditional transfer of control
- CALL: Subroutine invocation
</li>
<li><b><format color="Orange">Logical operations</format></b>:

- AND: Bitwise AND operation
- OR: Bitwise OR operation
- XOR: Bitwise exclusive OR operation
</li>
</list>

<p>These instruction sets can be either CISC (Complex Instruction Set Computing) or RISC (Reduced 
Instruction Set 
Computing)</p></li>
<li><b><format color="CornFlowerBlue">Bits used to Represent Data</format></b>: 
<p>Different data formats and their binary representation: </p>
<list>
<li><b><format color="Orange">Integer numbers</format></b>:

- 8-bit (byte): Range -128 to 127 
- 16-bit (short): Range -32,768 to 32,767
- 32-bit (int): Range -2^31 to 2^31-1 
- 64-bit (long): Range -2^(63) to 2^63-1
</li>

<li><b><format color="Orange">Floating-point numbers (IEEE 754)</format></b>:

- Single precision (32-bit): 1 bit sign, 8 bits exponent, 23 bits mantissa 
- Double precision (64-bit): 1 bit sign, 11 bits exponent, 52 bits mantissa
</li>
<li><b><format color="Orange">Characters</format></b>:

- ASCII: 7-bit encoding (128 characters)
- Extended ASCII: 8-bit encoding (256 characters)
- Unicode: Variable-length encoding (UTF-8, UTF-16, UTF-32)
</li>

<li><b><format color="Orange">Boolean values</format></b>:

- 0: False
- 1: True 

Typically stored as a single byte despite needing only 1 bit
</li>

<li><b><format color="Orange">Instructions</format></b>:

- Opcode: Operation code identifying the instruction
- Operands: Data or addresses the instruction operates on
- Format varies by architecture (16, 32, or 64 bits)
</li>
</list>
</li>
<li><b><format color="CornFlowerBlue">I/O Mechanisms</format></b>: 
Methods for data transfer between CPU and external devices:

- Programmed I/O (PIO)
- Interrupt-driven I/O
- Direct Memory Access (DMA)
- Memory-mapped I/O
- Port-mapped I/O (isolated I/O)
</li> 

<li><b><format color="CornFlowerBlue">Memory Addressing Techniques</format></b>: 
Methods to access data in memory:

- Direct addressing
- Indirect addressing
- Base + offset addressing
- Indexed addressing
- Stack addressing
- Register addressing
</li>
</list>
</procedure>
<p>Effectively, then, computer architecture is related directly to those areas of the computer 
that <code>affect the logical execution of our programs</code>, our code, and generally the way 
whatever we write executes in the CPU.</p>

### What is Computer Organization
<p>Organization refers to the hardware, design decisions, and their interconnections designed 
to realize architectural specifications. The following listing shows some parameters closely 
linbked with computer organization</p>
<procedure title="Example Topics Related to Computer Organization" collapsible="true">
<list columns="1">
<li><b><format color="CornFlowerBlue">Control Signals</format></b>: 
<p>Electronic signals that coordinate the operations of different computer components. These include:</p>
<list>
<li><b><format color="Orange">Clock Signals</format></b>:

- System Clock: Primary timing reference
- Clock Cycle: Basic unit of operation timing
- Clock Speed: Frequency of operation (MHz/GHz)
</li>
<li><b><format color="Orange">Memory Control</format></b>:

- Read Enable: Activates memory read operation
- Write Enable: Activates memory write operation
- Memory Select: Chooses memory bank/module
</li>
<li><b><format color="Orange">Bus Control</format></b>:

- Bus Request: Device requesting bus access
- Bus Grant: CPU allowing bus access
- Bus Busy: Indicates bus in use
</li>
<li><b><format color="Orange">Interrupt Signals</format></b>:

- IRQ: Interrupt Request
- INTA: Interrupt Acknowledge
- NMI: Non-Maskable Interrupt
</li>
</list>
</li>

<li><b><format color="CornFlowerBlue">Interfaces between computer and peripherals</format></b>: 
<p>Physical and logical connections for data transfer between computer and external devices:</p>
<list>
<li><b><format color="Orange">Serial Interfaces</format></b>:

- USB: Universal Serial Bus
- UART: Universal Asynchronous Receiver/Transmitter
- SPI: Serial Peripheral Interface
</li>
<li><b><format color="Orange">Parallel Interfaces</format></b>:

- PCI: Peripheral Component Interconnect
- PCIe: PCI Express
- AGP: Accelerated Graphics Port
</li>
<li><b><format color="Orange">Storage Interfaces</format></b>:

- SATA: Serial ATA
- NVMe: Non-Volatile Memory Express
- SCSI: Small Computer System Interface
</li>
<li><b><format color="Orange">Network Interfaces</format></b>:

- Ethernet: Network communication
- Wi-Fi: Wireless networking
- Bluetooth: Short-range wireless
</li>
</list>
</li>

<li><b><format color="CornFlowerBlue">Memory Technology Used</format></b>: 
<p>Different types of memory technologies and their characteristics:</p>
<list>
<li><b><format color="Orange">Primary Memory</format></b>:

- SRAM: Static Random Access Memory
- DRAM: Dynamic Random Access Memory
- Cache Memory: L1, L2, L3 cache levels
</li>
<li><b><format color="Orange">Secondary Memory</format></b>:

- HDD: Hard Disk Drive
- SSD: Solid State Drive
- Optical Storage: CD/DVD/Blu-ray
</li>
<li><b><format color="Orange">Non-Volatile Memory</format></b>:

- ROM: Read Only Memory
- EEPROM: Electrically Erasable ROM
- Flash Memory: NAND/NOR based
</li>
<li><b><format color="Orange">Special Purpose Memory</format></b>:

- Video Memory: VRAM
- Graphics Memory: GDDR
- Buffer Memory: For I/O operations
</li>
</list>
</li>
</list>
</procedure>
<p>Despite the clear differences, to some extent of these two topics, there is a grey area 
between organization and architecture, something that can be seen in the next image</p>

### Grey Area between Computer Organization and Architecture
<procedure style="choices">
<img alt="image.png" src="OrganizationAndArchitecture.png" border-effect="rounded"/>
</procedure>
<p>There is an area where we collide in between the two scopes of each. This path is known as 
the <code>Data Path</code></p>
<procedure title="The Data Path: Intersection of Architecture and Organization" collapsible="true">
<list>
<li><b><format color="CornFlowerBlue">Definition</format></b>:
<p>The data path is the actual hardware implementation that processes instructions and data flow through the computer system. It serves as the physical manifestation of both architectural requirements and organizational implementation. This dual nature makes it a critical component where design meets implementation.</p>
</li>

<li><b><format color="CornFlowerBlue">Key Components</format></b>:
<p>The data path consists of two main types of elements:</p>

<p><b><format color="Orange">Processing Elements</format></b>: At its core, the data path 
includes the <code>Arithmetic Logic Unit (ALU)</code> for computations, <code>registers</code> 
for temporary storage, the <code>Control Unit</code> for operation coordination, and the <code>Data 
and Address Buses</code> for information transfer. These components work together to execute 
instructions and process data.</p>

<p><b><format color="Orange">Control Elements</format></b>: The operation of processing elements 
is coordinated through <code>clock signals</code> that provide timing, <code>control signals</code> that direct 
operations, <code>status flags</code> that indicate conditions, and <code>pipeline stages</code> 
that enable concurrent execution.These elements ensure synchronized and efficient operation of 
the system.</p>
</li>

<li><b><format color="CornFlowerBlue">Why It's the Intersection</format></b>:
<p>The data path represents the meeting point of theoretical design and practical implementation 
through two perspectives:</p>

<p><b><format color="Orange">Architectural Perspective</format></b>: From this viewpoint, the 
data path implements the Instruction Set Architecture (ISA), determining how instructions are 
executed and defining data flow patterns. It provides the physical means to support 
architectural requirements and ensures that the theoretical design can be realized.</p>

<p><b><format color="Orange">Organizational Perspective</format></b>: This aspect focuses on the 
physical implementation of components, including hardware interconnections, timing and 
synchronization mechanisms, and performance optimization techniques. It addresses the practical 
challenges of turning architectural specifications into working hardware.</p>
</li>

<li><b><format color="CornFlowerBlue">Integration Points</format></b>:
<p><b><format color="Orange">Instruction Execution</format></b>: The data path implements the 
fundamental instruction cycle through distinct stages: fetch, decode, execute, memory access, 
and write back. Each stage represents a crucial step in instruction processing and demonstrates 
how architectural requirements are met through organizational implementation.</p>

<p><b><format color="Orange">Performance Considerations</format></b>: The effectiveness of the 
data path is measured through various metrics including clock cycle time, pipeline depth, 
handling of data dependencies, and resource utilization. These factors reflect both 
architectural decisions and organizational constraints, highlighting the intersection of theory 
and practice.</p>
</li>
</list>
</procedure>


## Structure and Function
<p>In general, a system can be abstracted onto structure and function, these two then determine 
the components and their communication for any and all process that the computer has to handle. 
These come from the idea of <code>hierarchical systems</code>, as sets of <b>interrelated 
subsystems nested until we reach some low level or elementary system</b>.
<br/><br/>
Through these we can abstract away certain sections of the data management and state control of 
our computer. For instance, abstracting onto its own section the way the computer must hande 
data management or storage, rather than having every detail within.
<br/><br/>
In order to understand this, then, we must first take a look at the computer from above, 
effectively as a whole and go down from there</p>
<procedure>
<img alt="AFunctionalViewOfTheComputer.png" src="AFunctionalViewOfTheComputer.png"/>
</procedure>
<p>Additionally, let us break down these conceptualizations into two groups, structure and 
function</p>


### Function
<p>Function refers to <code>the operation of each individual component as part of the 
structure.</code> Therefore, what we are saying then is that function takes care of the 
operationsof these components. And as such there should be various ways for them to work 
together (based on the diagram above).
<br/><br/>
These ways are shown in the following graph, as well as a little definition of each</p>
<procedure title="Structure And Function | Possible Computer Operations" collapsible="true">
<img alt="PossibleComputerOperations.png" src="PossibleComputerOperations.png"/>
<tabs>
<tab title="Path One | Movement and Control" collapsible="true">
<p>
In general <format style="italic">a computer must be able to move data between itself and 
the outside world</format>. To do so, it relies on devices that serve as <code>sources or 
destinations of data</code>. <br/><br/>
These can be further divided into two groups <code>Input/Output</code> (if the device is 
connected to our computer directly), or <code>Data Communications</code> (if the data 
transmitted or receive is done through longer distances).
</p>
</tab>
<tab title="Path Two | Movement, Control, and Storage">
<p>
In general, <format style="italic">a computer must be able to move and storage data 
between itself and the outside world</format>. To do so, it must rely on <code>read/write</code> 
operations done with its own storage.
</p>
</tab>
<tab title="Path Three | Storage, Control, and Processing">
<p>
in general, <format style="italic">a computer must be able to process the data it has on 
storage</format>. To do so, it will rely on the previous <code>read/write</code> operations, with 
the added step of processing the information to produce some output that will be stored locally.
</p>
</tab>
<tab title="Path Four | Movement, Control, Storage, Processing">
<p>
In general, <format style="italic">a computer must be able to process data, store data and 
even output data in the same data flow</format>. This kind of process requires all of the 
interconnecting parts of our computer to work in tandem.
</p>
</tab>
</tabs>
</procedure>

### Structure
<p>Structure is known as the <code>way in which a computer's components are interrelated</code>.</p>
<procedure>
<img alt="image.png" src="ComputerStructureGeneralView.png"/>
</procedure>
<procedure title="Computer Components and Their Interactions" collapsible="true">
<list>
<li><b><format color="CornFlowerBlue">Definition</format></b>:
<p>A computer is an integrated system of components that work together to process, store, and transfer data. It represents a complete information processing system that can execute programs and manipulate data through its interconnected components.</p>
</li>

<li><b><format color="CornFlowerBlue">Key Components</format></b>:
<p><b><format color="Orange">Input/Output (I/O)</format></b>: The interface between the computer and external world. It handles data transfer between the computer and peripheral devices, manages different data formats, and controls communication protocols. I/O operations can be synchronous or asynchronous, and may use interrupts or direct memory access.</p>

<p><b><format color="Orange">Main Memory</format></b>: The primary storage system that holds both programs and data currently in use. It provides fast, direct access storage using RAM technology, organized in a hierarchy of cells, words, and blocks. Memory operations are synchronized with the CPU through the memory controller.</p>

<p><b><format color="Orange">System Bus</format></b>: The primary communication pathway between major components. It consists of address, data, and control lines that enable component interaction. The system bus manages data transfer timing, arbitration between components, and maintains protocol standards for reliable communication.</p>

<p><b><format color="Orange">CPU</format></b>: The processing heart of the computer that executes instructions and performs calculations. It coordinates all computer operations, processes data according to instructions, and manages the flow of information between components.</p>
</li>
</list>
</procedure>

<procedure title="CPU Components and Operations" collapsible="true" caps="aswritten">
<list>
<li><b><format color="CornFlowerBlue">Definition</format></b>:
<p>The Central Processing Unit (CPU) is the computational core that executes instructions and coordinates system operations. It processes data according to stored program instructions and manages the flow of data between different computer components.</p>
</li>

<li><b><format color="CornFlowerBlue">Key Components</format></b>:
<p><b><format color="Orange">Registers</format></b>: High-speed storage locations within the CPU that hold instructions, data, and addresses. They include general-purpose registers for temporary data storage, special-purpose registers for specific operations, and status registers for condition flags.</p>

<p><b><format color="Orange">Arithmetic Logic Unit (ALU)</format></b>: The computational engine that performs arithmetic and logical operations. It processes binary data according to instructions, handles data comparisons, and generates condition flags based on operation results.</p>

<p><b><format color="Orange">Internal Bus</format></b>: The communication pathway within the CPU that connects its various components. It transfers data between registers, the ALU, and the control unit, operating at the CPU's core frequency for high-speed data movement.</p>

<p><b><format color="Orange">Control Unit</format></b>: The command center that coordinates all CPU operations. It fetches and decodes instructions, generates timing and control signals, and manages the sequence of operations for instruction execution.</p>
</li>
</list>
</procedure>

<procedure title="Control Unit Components and Functions" collapsible="true">
<list>
<li><b><format color="CornFlowerBlue">Definition</format></b>:
<p>The Control Unit orchestrates the operation of the CPU by managing instruction execution and coordinating component activities. It interprets instructions and generates the necessary control signals to execute them properly.</p>
</li>

<li><b><format color="CornFlowerBlue">Key Components</format></b>:
<p><b><format color="Orange">Sequencing Logic</format></b>: The timing mechanism that coordinates the execution of instructions. It generates the sequence of control signals needed for each instruction phase, manages the instruction cycle, and handles interrupts and exceptions.</p>

<p><b><format color="Orange">Control Unit Registers and Decoders</format></b>: Specialized storage and interpretation circuits that hold instruction information and convert it into control signals. This includes the instruction register, instruction decoder, and various control registers that maintain the CPU's state.</p>

<p><b><format color="Orange">Control Memory</format></b>: Storage for microcode or hardwired control signals that define how each instruction should be executed. In microprogrammed control units, it stores the detailed sequences of control signals needed for each instruction; in hardwired designs, it's implemented through fixed logic circuits.</p>
</li>
</list>
</procedure>

