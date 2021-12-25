// genetic-algorithm-robots-meher.cpp
// Ishan Meher, CISP 400
// 12/17/2020
/**
 * For this class we were not allowed to use multiple files as it made it hard for the professor to grade the assignment.
 * We are not allowed to use STL containers such as std::map and std::vector in this class 
*/

// Includes 
#include<iostream>
#include<string>
#include<ctime>
#include<fstream> 
#include<chrono>
#include<thread>

using namespace std;

// Vector Class
/**
 * Resizable array implementation of the Vector Abstract Data Type.
 * Dynamic memory allocation.
 **/
template <class A>
class Vector
{
	// The template class Vector creates an array that is able to store any data type 
	public:

		int length=0; // The length of the array
		A* array; // The array

	public:
		
    // Constructor with a predefined size
		Vector(int size)
		{	
			// Defines an Vector Object that accepts a length
			// Allocates space on the heap to store array
			if(length>=0)
			{
				// Makes sure the length is at least 0
				this->length=size;
				
			}			
			array= new A[length];
		}

    // Default Constructor
		Vector()
		{
			// Creates an Vector object
			// Allocates space on the heap to store array
			this->length=0;
			array=new A[length];

		}

  // Removes the last element of the array
  void removeLast()
  {
    remove(size()-1);
  }

	private:
    // resize the array
		void resizeVector()
		{
			// Resiszes the array by one
			A* tempVector= new A[length+1]; // The tempVector stores all the data of array and has one more element

			for(int position=0; position < length; position++)
			{
				// Loops through each position of the array and stores copies the element at each position into the tempVector
				tempVector[position]= array[position];
			}

			// Frees the memory used by the smaller array
			// The gradeList is set to point to the tempVector memory location
			delete[] array; 
      //array=nullptr;
			array=tempVector;	
			//tempVector=nullptr;
		}

	public:
    // Changes the element at an index
		void set(int index, A element)
		{
			// Changes the data stored at the requested index
			
				if(isValidIndex(index))
				{
					array[index]=element;
				}		
			
		}

    // Overlaod the equal operator
    Vector& operator =(const Vector& vector)
		{
			delete this->array;
      this->array=vector.array;
			return *this;
		} 

    // Copy Constructor  
    Vector(Vector& vector)
		{	
            	delete this->array;
      this->array=vector.array;
		}
  
    // Clear the array
		void clear()
		{
			// clears the contents of the arrray
			delete[] array;
			//array=nullptr;
			length=0;
			array= new A[length]; 
		}

    // Returns the size of the array
		int size()
		{
			// Returns the size of the array
			return length;
		}

    // Adds an element at the end of ther list
    void add(A element)
		{
			// Adds a new element to the end of the array
			// Increases the size of the array by one
			resizeVector();
						
			array[length]=element;
			length++;		
			
		}

    // Checks if the index is valid
		bool isValidIndex(const int index)
		{
			// Checks if the index entered is within the bounds of the array
			return (index>=0&&index<length);
		}

    // Gets the data at an index
		A get(const int index)
		{
			// Gets the data stored at the requested index
			// Returns the last index of the array if the requested index is invalid
			if(isValidIndex(index))
			{	
				return array[index];
			}
			else
			{
				// If the entered index is not valid returns value of last index
				return (array[length-1]);
			}
		}

    // Prints an item at an index
		void printItem(int index)
		{	
				// Prints the item at the requested index
				cout<<array[index];
			
			
		}

    // Prints the content of the array
		void printContents()
		{
			// Prints the the entire array
			for(int index=0;index>size();++index)
			{
				printItem(index);
			}
		}

    // Removes an element at an index
		void remove(const int index)
		{
			// Removes an alement at any index of the array
			if(isValidIndex(index))
			{
				// If the index is a valid index then remove the element located at the position


				// Defines a temporary array allocated on the heap
				// The int copyPosition variable increases with the loop unless the position that is to be removed is reached
				// By not increasing int copyPosition it will make sure that one less item will be copied;
				A* tempVector = new A[length-1];
				int copyPosition=0;
				for(int position=0;position<length;position++)
				{

					if(!(position==index))
					{
						tempVector[copyPosition]=array[position];
						copyPosition++;
						

					}
				}
				delete[] array;
				length--;
				array=tempVector;
				tempVector=nullptr;
			}
			
		}
		
    // Vector Unit Test
		void VectorUnitTest()
		{
			// Tests various functions of the Vector Class

			Vector<string> array;

      cout<<"Vector Unit Test\n";
			cout<<"Printing Initial Size:\n"<<array.size()<<'\n';
			cout<<"Adding an element:\n";
			array.add("Ishan Meher");
			cout<<"Printing Added element\n"<<array.get(0)<<'\n';
			

			cout<<"Adding a few Elements and printing these elements"<<'\n';
			array.add("Professor Fowler");
			cout<<"Printing the newly added element\n";
			cout<<array.get(1)<<'\n';
			array.add("Knuth");
			array.add("Warshall");
			array.add("Kruskal");

			cout<<"Printing All the elements in the array"<<'\n';
			for(int i=0;i<array.size();i++)
			{
				cout<<array.get(i)<<'\n';
			}
			cout<<'\n';

			cout<<"Removing last element(Kruskal is gone)\n";
			array.removeLast();

			for(int i=0;i<array.size();i++)
			{
				cout<<array.get(i)<<'\n';
			}

			array.remove(3);

			cout<<'\n';
			cout<<"Removing Warshall at index 2\n";			
			for(int i=0;i<array.size();i++)
			{
				cout<<array.get(i)<<'\n';
			}

			cout<<"Removing all elements"<<'\n';
			array.clear();
			
			cout<<"Adding element to cleared array\n";
			array.add("Ishan");
			cout<<array.get(0)<<'\n';
			cout<<array.size()<<'\n';
			cout<<"Changing the value of an index\n";
			array.set(0,"Professor Fowler");
			cout<<array.get(0)<<'\n';
			cout<<'\n';
		}
		
    // Destructor
		~Vector()
		{
      // Runs when the object goes out of scope of the

      // Free the array from memory
			delete[] array;

      // Set the array's pointer to nullptr
			array=nullptr;
			this->length=0;
		}	

};

/**
 * Grid Class 
 * Used to create the map for the robots to traverse the
 */
class Grid
{	
	public:
	int gridXSize;  // The number of rows in the grid (Horizontal size)
  int gridYSize;  // The number of columns in the grid (Vertical size)  
	string** grid;  // The string array
	
  // Constructor of a  square grid with predefined map
	Grid(const int gridSize)
	{
    // 
		this->gridXSize=gridSize; // Sets the number of rows in the grid
    this->gridYSize=gridSize; // Sets the number of columns in the grid
		this->grid=make2DArray(); // Creates the 2D array based on the grid dimensions
	}

  // Default constructor
	Grid()
	{
		this->gridXSize=10; // Sets the number of rows in the grid (10 array cells)
    this->gridYSize=10; // Sets the number of columns in the grid (10 array cells)
		this->grid=make2DArray(); // Creates the 2D array based on the grid dimensions
	} 

  // Able to cerate a rectangular grid
  Grid(int xSize,int ySize)
  {
    this->gridXSize=xSize;  // Sets the number of rows in the grid
    this->gridYSize=ySize;  // Sets the number of columns in the grid
		this->grid=make2DArray(); // Creates the 2D array based on the grid dimensions
  }

  // Destructor of the grid when the grid goes out of scope
	~Grid()
	{
    // Free the grid from memory
    delete[] grid;
	}

  // Checks to see if the grid is empty
  bool PositionisEmpty(int xCoord,int yCoord)
  {
    return this->grid[xCoord][yCoord]=="";
  }

  // Print the grid object by overloading the << operator
  friend ostream& operator <<(ostream& output, Grid& grid)
  {
    output<<"==============================\n";
    for(int i=0;i<grid.gridXSize;i++)
    {
      for(int j=0;j<grid.gridYSize;j++)
      {
        if(grid.grid[i][j]=="")
        {
          output<<"[ ]";
        }
        else
        {
          string text=grid.grid[i][j];
          output<<"["+text+"]";
        }
      }
      output<<'\n';
    }
   output<<"==============================\n";
    
    return output;
  }

  // Unit Testing of the Grid
  static void gridUnitTest()
  { 
    cout<<"Grid Unit Test\n";
    Grid grid(2);
    cout<<"Testing the loading of the parameterized Constructor\n";
    cout<<"Printing the Empty grid (The result of the constructor)\n"<<'\n';
    cout<<"Printing a 2x2 grid\n";
    cout<<grid;
   

    cout<<"Testing the Default constructor"<<'\n';
    Grid defaultGrid;
    cout<<"Also testing the addition of an string to the grid\n";
    for(int i=0;i<defaultGrid.gridXSize;i++)
    {
      for(int j=0;j<defaultGrid.gridYSize;j++)
      {
        string row= to_string(i);
        string col= to_string(j+1);
        
        defaultGrid.addToPosition(i,j,row+col);
      }
    }
    cout<<defaultGrid<<'\n';

    defaultGrid.printGrid();
  }

  // Prints the grid
  void printGrid()
  {
    for(int i=0;i<gridXSize;i++)
    {
      for(int j=0;j<gridYSize;j++)
      {
        cout<<grid[i][j];
      }
      cout<<'\n';
    }
  }

  // Adds a string to a position in the grid
  /**
   * Used to add elements onto the grid with a specified position
   * Primarily used to change the grid position
   * Some string elements are added to the grid include: The robot, batteries and the robots trail
   */
  void addToPosition(int row,int column,string text)
  {
    // Checks if the index is within the bounds of the grid
    // Mainly used to prevent segmentation faults
    if(row<gridXSize&&column<gridYSize)
    {
      string textValue=text;
      grid[row][column]=textValue;
    }
  }

	public:
  // Creates a 2D array based on the grid dimensions
	string** make2DArray()
	{
    // Pointer to the string array
		string** array;
    // Define the number of rows that the array wili have
		array= new string*[this->gridXSize];

    // Adds a column array to each row of the grid
		for(int index=0;index<this->gridXSize;index++)
		{
			array[index]= new string[this->gridYSize];
      
		}
    return array;
	}

  // Gets the string at a specified position
	string getValue(int x,int y)
  {
		return grid[x][y];
	}
  
};


/**
 * Functor to generate a random number
 * Mainly used to save me time from of reacting a random number generator for each class
 */
class RandomNumberGenerator
{
  public:

  int operator()(int lo,int hi)
  {
    // Generates a random number between lo and hi    
      int random= ( rand()%((hi - lo) + 1) + lo); 
      return random;
  }
};

/** 
 * Functor for enter key
 * Used several times throughout the program
 */ 
class EnterKey
{
  public:
  void operator()()
  {
    // Clears the console and asks the user to press the enter key to contine
	 int enter=0;
        
        cout << "Press Enter key to Continue\n";
        while (enter==cin.get() )      
		    {
                if ( enter == (int)'\n' ) 
                {
                    
                    break;
                }
                else 
                {
                    cout << "Failure, Program Quitting\n";
                    exit(EXIT_FAILURE);
                }
        }
  }
};

/**
 * Sensor Struct
 * Used to store the sensor data
 * The sensorState represents the reading of the sensor of the position that the robot plans to move next
 * There are 3 states: Empty(0), Wall(1) ,Battery(2), Not a wall can be either empty or battery(3-Optional State)
 # The orientation of the sensor is the cardinal direction that the robot is too move (N,S,E,W)
 */
struct Sensor
{
  // The sensorState represents the reading of the sensor of the position that the robot plans to move next
  // There are 3 states: Empty(0), Wall(1) ,Battery(2), Not a wall can be either empty or battery(3-Optional State)
  int sensorState;
  char orientation; // The direction the robot will move
  
  // Constructor that sets the orientiation that the robot will move to next
  Sensor(char orientation)
  {
    this->orientation=orientation;
  }
  
  // Constructor that sets the sensorState and the sensor's orientation
  Sensor(int sensorState,char orientation)
  {
    this->orientation=orientation;
    this->sensorState=sensorState;
  }
  
  // Overloading the << operator to print the sensor data
  friend ostream& operator << (ostream& output,Sensor& sensor)
  {
    output<<"Sensor State: "<<sensor.sensorState<<'\n';
    output<<"Sensor Orientation: "<<sensor.orientation<<'\n';
    return output;
  }

  // Overloading the == operator to compare two sensors
  bool operator==(Sensor& sensor)
  {
    return (sensor.sensorState==this->sensorState&&this->orientation==sensor.orientation);
  }
};


/**
 * Gene Class
 * Used to store the genes of the robot
 * The genes are the instructions that the robot will follow
 * The genes are stored in a Vector of Sensor structs
 */
class Gene
{
  public:
  // A "gene" has a vector of sensors
  Vector<Sensor*>* gene= new Vector<Sensor*>; // The gene is an array of Sensor structs
  RandomNumberGenerator rand; // Instantiate the random number generator to generate random numbers
  
  // Constructor for the ith gene where i is between 0 and 15 (There are 16 genes)
  Gene(int position)
  {
    // The 1st-15th gene have 5 sensors 
    if(position<15&&position>=0)
    {     
      this->gene= new Vector<Sensor*>(5);
    }
    // The -th position has 4 genes (Used for debugging)
		else if(position<0)
		{
			this->gene= new Vector<Sensor*>(4);
		}		
    // The 16th gene has 1 sensor
    else if(position==15)
    {
      this->gene= new Vector<Sensor*>(1); 
    } 
    makeGene(position);
    
  }

  // Overloads teh equal operator to assign one gene to another
  Gene& operator =(const Gene& gene)
	{
		this->gene=gene.gene;
		return *this;
	}

  // Copy constructor for the gene
  Gene(const Gene& gene)
	{
		this->gene=gene.gene;
	}
  
  // Destructor for the gene Runs when the gene goes out of scope
  ~Gene()
  {
    // Deletes the gene
    delete this->gene;
  }
  
  void makeGene(int position)
  {
    // There are five sensors inside a "gene"
    char array[] = {'n','s','w','e'};
    char sensorOrientation;
    int sensorState;

      for(int i=0;i<this->gene->size();i++)
      {
        // The first 3 genes store sensor states
        // The fourth gene stores behavior
        if(i<4)
        {
           // O is empty
           // 1 is wall
           // 2 is battery
           // 3 is not a wall
           sensorState=rand(0,3);
           sensorOrientation=array[i];
          
          // The 15th gene is used to perform the default behavior when none of the genes match the robot's positional readings
          if(position==15)
          {
            sensorOrientation=array[rand(0,3)];
            sensorState=1;
          }
        }
        else
        {
          // The position of the gene that determines the command;
					sensorState=1;
          sensorOrientation=array[rand(0,3)];
          
        }
        Sensor* sensor= new Sensor(sensorState,sensorOrientation);
        this->gene->set(i,sensor);
      }
  }


  static void GeneUnitTest()
  {
    Gene gene(1);
    cout<<"Gene Unit Test\n";
    cout<<gene;
  }

  void printGene(int index)
  {
    //cout<<"Sensor: "<<index<<"\n"<<*this->gene->get(index);
  }

  friend ostream& operator <<(ostream& output,Gene& gene)
  {
    for(int i=0;i<gene.gene->size();i++)
    {
      output<<"Sensor: "<<i+1<<'\n';
    }
    return output;
  }


};


class Robot
{
  public:
  
  Vector<Gene*>* genome= new Vector<Gene*>(16); // robot's genome an array of genes
  Gene* sensor = new Gene(-1);
	
  Grid* grid= new Grid(10); // Store the path that the robot moved
  int health=5; // The lifespan of the robot
  int lifespan=0; // Stores how many moves the robot survives for
  int fitness=0;
  RandomNumberGenerator rand;
	
  // The coordinates of the robot
  int xCoord;
  int yCoord;

	Robot& operator =(const Robot& robot)
	{
		
		this->lifespan= robot.lifespan;
    this->fitness=robot.fitness;
		this->xCoord=robot.xCoord;
		this->yCoord=robot.yCoord;
		this->genome= robot.genome;
		this->sensor= robot.sensor;
		return *this;
	}


  Robot(const Robot& robot)
	{
		
		this->lifespan= robot.lifespan;
    this->fitness=robot.fitness;
		this->xCoord=robot.xCoord;
		this->yCoord=robot.yCoord;
		this->genome= robot.genome;
		this->sensor= robot.sensor;
		
	}


  Robot()
  {
    // Assign a grid to a robot
    // Add all 16 genes to the robot
    addGenesToRobot();
    populateGrid();
    
    
		
  }

  Robot(Robot& parent1,Robot& parent2,int parity)
  {
    // Make a new robot from two parents
    reproduction(parent1,parent2,parity);
    populateGrid();

    
  }

  ~Robot()
  {
    delete genome;
    delete grid;
		delete sensor;

  }


  void sensorData()
  {

    // Stores the current Sensor Data
    // Return a 0 code for empty
    // A 1 code for wall 
    // A code 2 for battery
    // Holds all the robots Sensor Readings


    int* sensorStates = returnSensorStates(this->xCoord,this->yCoord);		
		
    for(int i=0;i<this->sensor->gene->size();i++)
		{
      this->sensor->gene->get(i)->sensorState=sensorStates[i];
    }

    delete [] sensorStates;
    sensorStates=nullptr;
  }

  int outputSensorState(int xCoord, int yCoord)
  {
     
    if(positionIsWall( xCoord,yCoord))
    {
      return 1;
    }
    else if(positionhasBattery(xCoord,yCoord))
    {
      return 2;
    }
    else if(positionIsEmpty(xCoord,yCoord))
    {
      return 0;
    }
    else
    {
      return -9;
    }
    
  }

  int* returnSensorStates(int xCoord,int yCoord)
  {
    
    int* sensorStates = new int[4];

    // Sensor at the north of the robot
    sensorStates[0]=outputSensorState(xCoord,yCoord+1);
    

    // Sensor at the south of the robot
    sensorStates[1]=outputSensorState(xCoord,yCoord-1);


    // Sensor reading at the west of the robot
		
    sensorStates[2]=outputSensorState(xCoord-1,yCoord);
		
    // Sensor reasding at the east of the robot
    sensorStates[3]=outputSensorState(xCoord+1,yCoord);
			
    return sensorStates;
		
  }
  void reset()
  {
   
    this->lifespan=0;
    this->fitness=0;
    this->health=5;
    delete this->grid;
    Grid* grid = new Grid();
    this->grid=grid;
    populateGrid();
  }


  bool positionIsWall(int xCoord,int yCoord)
  { 
    int gridSize= this->grid->gridXSize;
    return (xCoord>=gridSize||yCoord>=gridSize||xCoord<0||yCoord<0);
  }

  bool positionhasBattery(int xCoord, int yCoord)
  {
   
      return(!positionIsWall(xCoord, yCoord)&&this->grid->grid[xCoord][yCoord]=="B");
    
  }

  bool positionIsEmpty(int xCoord, int yCoord)
  {
    // return true If the position does not have a wall or battery
    // return true if the position has a blank
    return((!positionhasBattery(xCoord,yCoord)&&!positionIsWall(xCoord,yCoord))||this->grid->grid[xCoord][yCoord]=="");
  }

 

  void reproduction(Robot& parent1,Robot& parent2,int parity)
  {
     
    // get the genes from both parents
    Vector<Gene*>* parent1Gene = addGenes(parent1,parity);
    Vector<Gene*>* parent2Gene= addGenes(parent2,parity);

   int index=0;
   while(index<this->genome->size())
   {
     
     this->genome->set(index,parent1.genome->get(index));
     this->genome->set(15-index,parent2.genome->get(15-index));
     index+=2;     
    
   }
   if(isMutatable(5))
   {
     // 5 percent chance of there being a mutation
     mutateRobot();
   }
   
   delete parent1Gene;
   delete parent2Gene;
   

  }

  Vector<Gene*>* addGenes(Robot& robot,int parity)
  {
    // Adds either the even genes or odd genes based on parameter
    // If parity is 1 add genes from odd postions
    // Else if parity is 2 add genes from even positions
    Vector<Gene*>* childGenome= new Vector<Gene*>(8);
    for(int i=0;i<robot.genome->size();i++)
    {
      if(parity==1)
      {
        if(i%2==1)
        {
          childGenome->set(i,robot.genome->get(i));
        }
      }
      else
      {
        if(parity==2)
        {
          if(i%2==0)
          {
            childGenome->set(i,robot.genome->get(i));
          }
          
        }
      }
    }
    return childGenome;
  }

  void mutateRobot()
  {
    
    int randomGene= rand(0,15);
    Gene* gene; // Gene to be added 
    if(randomGene<15&&randomGene>=0)
    {
      // If the gene to be mutated is not the last gene
      // Change the non-default gene
       gene= new Gene(0);
    }    
    else if(randomGene==15)
    {
      // Change the default action gene
      gene=new Gene(15);
    }
    
    this->genome->set(randomGene,gene);
  }

  bool isMutatable(int mutationRate)
  {
    // Roll a random number betweewn 0 and 100
    // If the number is less or equal to the mutation rate then the robot can be mutated
    int mutation = rand(0,100);
    return (mutation<=mutationRate);
  }

  void addGenesToRobot()
  {
    // Adds all 16 genes to the robot
    
    int index=0;
    
    while(index<genome->size())
    {   
        Gene* gene= new Gene(index);
        this->genome->set(index,gene);
        index++;  
    }
    
	} 

   static void robotUnitTest()
  {
    cout<<"Robot Unit Tests\n";
    Robot robot1;
  
    robot1.robotLifeCycle();
    //cout<<robot1<<'\n';
      
    Robot robot2;
    robot2.robotLifeCycle();
    //cout<<robot2<<endl;
    
    Robot robot3(robot1,robot2,1);
    robot3.robotLifeCycle();   
    cout<<robot3;

  }

  friend ostream& operator <<(ostream& output,Robot& robot)
  {
		int xCoord=robot.xCoord;
		int yCoord=robot.yCoord;
    output<<"=============================================\n";;
    output<<"Robot Grid:\n"<<*robot.grid;
     cout<<"Life Data:\n";
		output<<"Robot Health: "<<robot.health<<'\n';
    output<<"Lifespan: "<<robot.lifespan<<'\n'; 
    output<<"*Robot Fitness(The number of batteries colleced by the robot): "<<robot.fitness<<'\n';
		output<<"======================\n";
		output<<"Map Code Legend:\n";
		output<<"Battery Code: B\n";
		output<<"Robot Code: R\n";
		output<<"Start Position Code: S\n";
    output<<"Past Position Code: @\n";
		output<<"======================\n";
		output<<"Sensor Code Legend:\n";
		output<<"Empty Space Code: 0\n";
		output<<"Wall Code: 1\n";
		output<<"Battery Code: 2\n";
		output<<'\n';

    cout<<"Robot Position:\n";
    output<<"X-Coordinate: "<<(xCoord)<<endl;
		output<<"Y-Coordinate: "<<(yCoord)<<endl<<endl;


		output<<"Sensor Locations\n";
		output<<"North\n";
		output<<"X-Coordinate: "<<(xCoord)<<endl;
		output<<"Y-Coordinate: "<<(yCoord+1)<<endl;
	
		output<<"South\n";
		output<<"X-Coordinate: "<<(xCoord)<<endl;
		output<<"Y-Coordinate: "<<(yCoord-1)<<endl;

		output<<"West\n";
		output<<"X-Coordinate: "<<(robot.xCoord-1)<<endl;
		output<<"Y-Coordinate: "<<(robot.yCoord)<<endl;

		output<<"East\n";
		output<<"X-Coordinate: "<<(1+xCoord)<<endl;
		output<<"Y-Coordinate: "<<robot.yCoord<<endl;
		cout<<"======================\n";

		output<<"Robot Sensor\n"<<*robot.sensor<<'\n';
		output<<"======================\n";
    
    for(int i=0;i<robot.genome->size();i++)
    {
      output<<"Gene: "<<i+1<<'\n';
      output<<*robot.genome->get(i)<<'\n';
    }
    output<<"=============================================\n";
    return output;
  }

  void populateGrid()
  {
    // Add a random number to grid
    string batteryCell = "B";
    string robotCell = "R";
    int numberOfCells=0;
    while(numberOfCells<41)
    {
      int xCoord = rand(0,9);
      int yCoord = rand(0,9);
      
      if(this->grid->PositionisEmpty(xCoord,yCoord))
      {
        
        if(numberOfCells<40)
        {
          this->grid->grid[xCoord][yCoord]=batteryCell;
          if(this->grid->grid[xCoord][yCoord]=="B")
          {
            
            numberOfCells++;
            
          }
        }
        else
        {
          this->grid->grid[xCoord][yCoord]=robotCell;
          if(this->grid->grid[xCoord][yCoord]=="R")
          {
            this->xCoord=xCoord;
            this->yCoord=yCoord;
            numberOfCells++; 
          }
        }
      }
    }
  }

  void robotLifeCycle(bool showMoves=false)
  {
   while(this->health>0)
   {
     if(showMoves)
     {
       cout<<*this->grid;
       cout<<"Health: "<<this->health<<'\n';
       cout<<"Batteries Collected(Fitness): "<<this->fitness<<'\n';
       cout<<"Number of moves made: "<<this->lifespan<<'\n';
       std::this_thread::sleep_for(std::chrono::milliseconds(700));
       
      system("clear");       
     }
     positionToMoveRobot();  
        
   } 
  }

  void positionToMoveRobot()
  {
    //Scans the Genes of the genome and compares it to the sensor
    //If the sensor is matched then the gene that is matched last sensor is used for movement

    // Get the most current Sensor Data
    sensorData();

    bool robotWasMoved=false; // Stores if the robot has been moved
    
    for(int i=0; i<this->genome->size();i++)
    {
      if(sensorIsMatched(*this->genome->get(i),*this->sensor))
      {      
        // orientation of the last sensor of the gene is used for movement
        moveBasedOnOrientation(this->genome->get(i)->gene->get(4)->orientation);
                  
        // Move the robot according to the instruction of the movement code if the movement is a valid position
        robotWasMoved=true;        
        break;
      } 
    }
    if(!robotWasMoved)
    {
      // If the robot was not moved move the robot based on the sensor data in the default sensor
      // The default sensor stores the orientation
      moveBasedOnOrientation( this->genome->get(15)->gene->get(0)->orientation);
     
  
    }
    this->lifespan++; // Increment the lifespan which stores how many turns the robot lived
    this->health--;
  }

  bool sensorIsMatched(Gene& gene,Gene& sensor)
  {
    // Loop through the gene and check if the gene matches with the sensor
    for(int i=0; i< sensor.gene->size();i++)
    {
      Sensor* geneSensor=gene.gene->get(i);
      bool matched=*gene.gene->get(i)==*sensor.gene->get(i);
      if(matched)
      {
        // If an exact mathch to the sensor state
      }
      else if(geneSensor->sensorState==3&&(sensor.gene->get(i)->sensorState==0||sensor.gene->get(i)->sensorState==2||sensor.gene->get(i)->sensorState==1))
      {
        // Don't really care if the sensor value is a battery or empty
      }
      else
      {
        return false;
      }
      
    }
    return true;
  }
 
  void moveRobot(int xCoord,int yCoord)
  {
    /*
     Move Robot
     Check if the position has a wall
     If the position has a battery then increase health by 5
    */
   
    if(!positionIsWall(xCoord,yCoord))
    {
      
      if(lifespan==0)
      {
        this->grid->grid[this->xCoord][this->yCoord]="S";
      }
      else
      {
        this->grid->grid[this->xCoord][this->yCoord]="@";
      }
      if(positionhasBattery(xCoord,yCoord))
      {
        this->health+=5;
        this->fitness++;
        
      }
      this->grid->grid[xCoord][yCoord]="R";
      this->xCoord=xCoord;
      this->yCoord=yCoord;
    }
  }


  void moveBasedOnOrientation(char orientation)
  {
    int xCoord=this->xCoord;
    int yCoord=this->yCoord;

    if(orientation=='n')
    {
      moveRobot(xCoord,yCoord+1);
    }
    else if(orientation=='s')
    {
      moveRobot(xCoord,yCoord-1);
    }
    else if(orientation=='w')
    {
      moveRobot(xCoord-1,yCoord);
    }
    else if(orientation=='e')
    {
      moveRobot(xCoord+1,yCoord);
    }
  } 

};


class Simulation
{
  public:

  Vector<Robot*>* population;
  Vector<double> averagePopulationFitness;
  int numberOfGenerations;
  EnterKey enter; 

  Simulation()
  {
    population= new Vector<Robot*>(200);
    this->numberOfGenerations=1000;
  }

  Simulation(int size,int numberOfGenerations)
  {
    if(size%2==0&&size>0&&numberOfGenerations>0)
    {
      // Make sure the population is even and not zero
      population= new Vector<Robot*>(size);
    
      this->numberOfGenerations=numberOfGenerations;
    }
    else
    {
      population= new Vector<Robot*>(2);
 
      this->numberOfGenerations=200;
      
    }
  }

  void storePopulationAverage()
  { 
    double sum=0;
    for(int i=0;i<this->population->size();i++)
    {
      sum+=this->population->get(i)->fitness;
    }
    this->averagePopulationFitness.add(sum/this->population->size());
  }

  
  void addRobots()
  {
    int index=0;
    int size=this->population->size();
    while(index<size)
    {
      Robot* robot= new Robot;
      this->population->set(index,robot);
      index++;
    }
  }
  
  void runSimulation()
  {
      // The entire population goes through the track
      addRobots();
      cout<<"Running simulation...\n";
      for(int i=0;i<this->numberOfGenerations;i++)
      { 
        runPopulationSimulation();
        storePopulationAverage();
        naturalSelection();
        matePopulation();
      }
      
      system("clear");
      
  }

  void runPopulationSimulation()
  {
    //cout<<"running simulation on population\n";
    for(int i=0;i<this->population->size();i++)
    {
      
      this->population->get(i)->reset();
      this->population->get(i)->robotLifeCycle();
      
    }      
  }

  void matePopulation()
  {
   
    Vector<Robot*>* nextGenerationPopulation = new Vector<Robot*>;
    
    int populationSize=this->population->size();
    if(populationSize>0)
    {
      for(int i=0;i<populationSize;i++)
      {
        Robot* parent1 = this->population->get(i);
        Robot* parent2 = this->population->get(i+1);

        Robot* child1 = new Robot(*parent1,*parent2,1);
        Robot* child2 = new Robot(*parent1,*parent2,2);
        
        nextGenerationPopulation->add(parent1);
        nextGenerationPopulation->add(parent1);
        nextGenerationPopulation->add(child1);
        nextGenerationPopulation->add(child2);
        i++;
       
      }
    }    
    this->population=nextGenerationPopulation;
  }

  
  void naturalSelection()
  {
      // Make a temporary array with size of half the population's size
      int populationSize=this->population->size()/2;
      if(populationSize>0)
      {
      Vector<Robot*>* remainingPopulation = new Vector<Robot*>(populationSize);
      
      for(int i=0;i<populationSize;i++)
      {
        // find the largest
        int largest=findLargest();
        
        // Add the Robot with the largest fitness
        remainingPopulation->set(i,this->population->get(largest));
        
        // Remove the current largest from the list
        this->population->remove(largest);        
      }
      // Add the largest half of the population to the population array
      //delete this->population;
      delete this->population;
      this->population=remainingPopulation;
    }
  }

  int findLargest()
  {
    // returns the index of the robot with the largest fitness
    int largest=this->population->get(0)->fitness;
    int index=0;
    for(int i=0;i<this->population->size();i++)
    {
      if(this->population->get(i)->fitness>largest)
      {
        index=i;
        largest=this->population->get(i)->fitness;
      }
    }
    return index;
  }

  friend ostream& operator << (ostream& output,Simulation& simulation)
  {
    EnterKey enter;
    cout<<"Simulation Unit Tests\n";
    cout<<"Printing the largest robot\n";
    cout<<*simulation.population->get(simulation.findLargest())<<'\n';
    enter();
    system("clear");
    output<<"Population Life Expectancies\n";
    for(int i=0;i<simulation.numberOfGenerations;i++)
    {
     
      cout<<"Generation: "<<i+1<<'\n';     
      output<<"Population Fitness: "<<simulation.averagePopulationFitness.get(i)<<'\n';
      if(i%100==0)
      {
        cout<<"Reached the max size of the console\n";
        enter();
        system("clear");
      }

    }
    return output;
  }

void savePopulationData()
  {
     ofstream outputFile;
        
        // opens the file
        outputFile.open("populationData-ishanmeher.txt");
        cout<<"Writing the data of the list to the file\n";     
        
        // Saves the length of the list to the file
        // Used to determine how many objects are read when the program runs again
        outputFile<<"Average Population Fitness\n";
        outputFile<<"Copy and Paste contents below into a spreadsheet program for to see a graph\n";
        outputFile<<"============================================================================\n";
        // Loops through the array and adds the contents of each object
        for(int index=0; index<this->numberOfGenerations;index++)
        {         
          outputFile<<this->averagePopulationFitness.get(index)<<'\n';
        }
        
        outputFile.close();
  }

  
  static void simulationunitTest()
  {
    cout<<"Simulation Unit Tests\n";
    Simulation simulation(200,1);
    simulation.runSimulation();
    cout<<simulation<<'\n'; 
  }

  void runFittestRobot()
  {
    int bestRobot= findLargest();
    runRobot(bestRobot);
  }

  void runRobot(int index)
  { 
    if(index<this->population->size())
    {
      Robot* robot= this->population->get(index);
      robot->reset();
      robot->robotLifeCycle(true); 
      cout<<*robot<<'\n';
    }
  }

};

// Function Prototypes
void UnitTests();
void ProgramGreeting();
int randomNumber();
void ProgramGreeting();
void enterKey();

int main()
{
  ProgramGreeting();
  enterKey();
  system("clear");
  Simulation* simulation= new Simulation(200,1000);
  simulation->runSimulation();
  simulation->savePopulationData();       
  cout<<*simulation<<'\n';
  cout<<"To see a graph copy and paste contents below the ====== of the txt file generated by the simulation\n";
  cout<<"Runnning the fittest robot over a grid\n";
  simulation->runFittestRobot();
  delete simulation;
  
}

void UnitTests()
{
  cout<<"Unit Tests\n";
  
  
  Vector<int> Vector;
  Vector.VectorUnitTest();
  
  enterKey();
  system("clear");

  Gene gene(1);
  Gene::GeneUnitTest();
  enterKey();
  system("clear");
  
  Grid grid;
  Grid::gridUnitTest();
  enterKey();
  system("clear");

  Robot robot1;
  Robot::robotUnitTest();
  enterKey();
  system("clear");
 
  Simulation::simulationunitTest();
  enterKey();
  system("clear");
  
}

void ProgramGreeting()
{
  srand(time(0));
  cout<<"Genetic Algorithm Robots\n";
  cout<<"========================\n";
  cout<<"Author:Ishan Meher\n";
  cout<<"Due Date: 12/17/2020\n";
  cout<<"CISP 400: Final Project\n";
  cout<<"Testing the effects of evolution on a population of robots by showing how the robot's population gradually improve their ability to collect batteries\n";
}


void enterKey()
  {
    // Clears the console and asks the user to press the enter key to contine
	 int enter=0;
        
        cout << "Press Enter key to Continue\n";
        while (enter==cin.get() )      
		{
                if ( enter == (int)'\n' ) 
                {
                    
                    break;
                }
                else 
                {
                    cout << "Failure, Program Quitting\n";
                    exit(EXIT_FAILURE);
                }
        }
  
  }
