// genetic-algorithm-robots-meher.cpp
// Ishan Meher, CISP 400
// 12/17/2020

#include<iostream>
#include<string>
#include<limits>
#include<cctype>
#include<ctime>
#include<fstream> 
#include<cstdlib>


using namespace std;

template <class A>
class Vector
{
	// The template class Vector creates an array that is able to store any data type 
	public:

		int length=0;
		A* array;

	public:
		
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


        Vector(Vector& vector)
		{	
            // Assign one Vector to another
			delete this->array;
            this->array=nullptr;
            this->array=vector.array;
		}


		Vector()
		{
			// Creates an Vector object
			// Allocates space on the heap to store array
			this->length=0;
			array=new A[length];

		}

  void removeLast()
  {
    remove(size()-1);
  }
		

	private:

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
			array=tempVector;	
			tempVector=nullptr;
		}

	public:

		void set(int index, A element)
		{
			// Changes the data stored at the requested index
			
				if(isValidIndex(index))
				{
					array[index]=element;
				}		
			
		}

    Vector& operator =(const Vector& vector)
		{
			delete this->array;
      this->array=vector.array;
			return *this;
		} 

		void clear()
		{
			// clears the contents of the arrray
			delete[] array;
			array=nullptr;
			length=0;
			array= new A[length]; 
		}

		int size()
		{
			// Returns the size of the array
			return length;
      
		}

	
		void add(A element)
		{
			// Adds a new element to the end of the array

			// Increases the size of the array by one
			resizeVector();
						
			array[length]=element;
			length++;		
			
		}

		bool isValidIndex(const int index)
		{
			// Checks if the index entered is within the bounds of the array
			return (index>=0&&index<length);
		}

		

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

		void printItem(int index)
		{	
				// Prints the item at the requested index
				cout<<array[index];
			
			
		}

		void printContents()
		{
			// Prints the the entire array
			for(int index=0;index>size();++index)
			{
				printItem(index);
			}
		}

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
		
		void VectorUnitTest()
		{
			// Tests various functions of the Vector Class

			Vector<string> array;
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
		
		~Vector()
		{
			delete[] array;
			array=nullptr;
			this->length=0;
		}	

};

class Grid
{	
	public:
	int gridSize;
	string** grid;
	
	Grid(const int gridSize)
	{
		this->gridSize=gridSize;
		this->grid=make2DArray(gridSize);
	}

	Grid()
	{
		this->gridSize=10;
		this->grid=make2DArray(10);
    
	} 

	~Grid()
	{
    
		for(int index=0;index<gridSize;index++)
		{
      // Delete all the columns of the array
      grid[index]=nullptr;
      delete grid[index]; 
			
      
		}
    // Delete array
    grid=nullptr;
    delete[] grid;

  
		
	}

  bool PositionisEmpty(int xCoord,int yCoord)
  {
    return this->grid[xCoord][yCoord]=="";
  }

  friend ostream& operator <<(ostream& output, Grid& grid)
  {
    output<<"==============================\n";
    for(int i=0;i<grid.gridSize;i++)
    {
      for(int j=0;j<grid.gridSize;j++)
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

  void gridUnitTest()
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
    for(int i=0;i<defaultGrid.gridSize;i++)
    {
      for(int j=0;j<defaultGrid.gridSize;j++)
      {
        string row= to_string(i);
        string col= to_string(j+1);
        
        defaultGrid.addToPosition(i,j,row+col);
      }
    }
    cout<<defaultGrid<<'\n';

    defaultGrid.printGrid();

  }

   
  void printGrid()
  {
    
    for(int i=0;i<gridSize;i++)
    {
      for(int j=0;j<gridSize;j++)
      {
        cout<<grid[i][j];
      }
      cout<<'\n';
    }
  }


 
  void addToPosition(int row,int column,string text)
  {
    if(row<gridSize&&column<gridSize)
    {
      string textValue=text;
      grid[row][column]=textValue;
    }
  }

	public:

	string** make2DArray(const int gridSize)
	{
		string** array;
    
		array= new string*[gridSize];
  
		for(int index=0;index<this->gridSize;index++)
		{
			array[index]= new string[gridSize];
      
		}
    return array;
	}

	string getValue(int x,int y)
	{
		return grid[x][y];
	}

  

};

class RandomNumberGenerator
{
  public:
  int operator()(int lo,int hi)
  {
    // Generates a random number between lo and hi
    //return (rand()% (hi-lo+1))+lo;

      int random= ( rand()%((hi - lo) + 1) + lo); 
      return random;
  
  }
};

struct Sensor
{
  int sensorState;
  char orientation;

  // Maybe have the manager randomly call randomNumberGenerator
  //RandomNumberGenerator randomNumberGenerator;

  Sensor(char orientation)
  {
    this->orientation=orientation;
    //this->sensorState=randomNumberGenerator(0,2);
  }
  Sensor(int sensorState,char orientation)
  {
    this->orientation=orientation;
    this->sensorState=sensorState;
  }
  
  friend ostream& operator << (ostream& output,Sensor& sensor)
  {
    output<<"Sensor State: "<<sensor.sensorState<<'\n';
    output<<"Sensor Orientation: "<<sensor.orientation<<'\n';
    return output;
  }

};



class Gene
{
  public:
  // A "gene" has six sensors
  Vector<Sensor*>* gene= new Vector<Sensor*>;
  
  Gene(int position)
  {
    if(position<15)
    {
      this->gene= new Vector<Sensor*>(5);
     
    }		
    else
    {
      this->gene= new Vector<Sensor*>(1); 
    } 
    makeGene(position);
    

  
  }
	

  ~Gene()
  {
    // Might fail cause vector is automatic delete
  }
  
  void makeGene(int position)
  {
    // There are five sensors inside a "gene"
    RandomNumberGenerator randomNumberGenerator;

    char array[] = {'n','s','w','e'};
    char sensorOrientation;
    int sensorState;
 
    
      for(int i=0;i<this->gene->size();i++)
      {

        // The first 3 genes store sensor states
        // The fourth gene stores behavior
        if(i<4)
        {
           sensorState=randomNumberGenerator(0,2);
           sensorOrientation=array[i];
          if(position==15)
          {
            sensorState=1;
          }
          
        }
        else
        {
          // The position of the gene that determines the command;
          int randomNumber=randomNumberGenerator(0,3);
          sensorState=1;
          sensorOrientation=array[randomNumber];
        }
        Sensor* sensor= new Sensor(sensorState,sensorOrientation);
        this->gene->set(i,sensor);
        
      }
    
    
  }


  void GeneUnitTest()
  {
    Gene gene(1);
    cout<<"Gene Unit Test\n";
    for(int i=0;i<gene.gene->size();i++)
    {
      //printGene(i);
    }

    cout<<gene;
  }

  void printGene(int index)
  {
    cout<<"Sensor: "<<index<<"\n"<<*this->gene->get(index);
  }

  friend ostream& operator <<(ostream& output,Gene& gene)
  {
    for(int i=0;i<gene.gene->size();i++)
    {
      output<<"Sensor: "<<i+1<<'\n';
      output<<*gene.gene->get(i);
    }
    return output;
  }


};


class Robot
{
  public:
 
  Vector<Gene*>* genome= new Vector<Gene*>(16); // robot's genome
  Vector<Gene*>* sensor= new Vector<Gene*>(1);
	
  Grid* grid= new Grid(10); // Store the path that the robot moved
  int health=5; // The lifespan of the robot
  int lifespan;

  // The coordinates of the robot
  int xCoord;
  int yCoord;

  Robot()
  {
    // Assign a grid to a robot
    // Add all 16 genes to the robot
    addGenesToRobot();
		loadSensorToRobot();
    populateGrid();
    //lifetime();
		loadSensorToRobot();
    sensorData();
		
  }

  Robot(Robot& parent1,Robot& parent2)
  {
    // Make a new robot from two parents
    reproduction(parent1,parent2);
    populateGrid();
		loadSensorToRobot();
		
    //lifetime();
    
  }

  ~Robot()
  {
    for(int i=0;i<genome->size();i++)
    {
      delete genome->get(i);
    }
      grid=nullptr;
    delete grid;
		delete sensor;
    
  }

  void lifetime()
  {
    /*
    while(this->health>0)
    {
      sensorData();
      lifespan++;
      moveRobot();
    }
    */
  }

  void sensorData()
  {
    // Return a 0 code for empty
    // A 1 code for wall 
    // A code 2 for battery
    // Holds all the robots Sensor Readings
    //int* sensorStates = returnSensorStates(xCoord,yCoord);
		cout<<"Gene\n";
    cout<<*this->sensor->get(0)<<endl;
		//cout<<gene;
		cout<<"End Gene\n";


		/*
    for(int i=0;i<this->sensor->get(0)->gene->size()-1;i++)
    {
			 cout<<"Loop\n";
			cout<< this->sensor->get(0)->gene->get(i)->sensorState<<'\n';
      this->sensor->get(0)->gene->get(i)->sensorState=sensorStates[i];
      
      // REMOVE
      cout<<"Diagnostics\n";
      cout<<this->sensor->get(0)->gene->get(i)->sensorState<<'\n';
    }
		*/
    //delete [] sensorStates;

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
      return 0;
    }
    
  }

  int* returnSensorStates(int xCoord,int yCoord)
  {
    cout<<"returnSensorStates(int xCoord,int yCoord)\n";
    int* sensorStates = new int[4];

    // Sensor at the north of the robot
    sensorStates[0]=outputSensorState(xCoord,yCoord+1);
    cout<<"returnSensorStates(int xCoord,int yCoord)\n";

    // Sensor at the south of the robot
    sensorStates[1]=outputSensorState(xCoord,yCoord-1);
    cout<<"returnSensorStates(int xCoord,int yCoord)\n";

    // Sensor reading at the west of the robot
    sensorStates[1]=outputSensorState(xCoord-1,yCoord);
    cout<<"returnSensorStates(int xCoord,int yCoord)\n";

    // Sensor reasding at the south of the robot
    sensorStates[1]=outputSensorState(xCoord+1,yCoord);
    

    return sensorStates;
  }
  

  bool positionIsWall(int xCoord,int yCoord)
  {
    int gridSize=this->grid->gridSize;
    return (xCoord>= gridSize||yCoord>=gridSize||xCoord<0||yCoord<0);
  }

  bool positionhasBattery(int xCoord, int yCoord)
  {
    if(!positionIsWall(xCoord, yCoord))
    {return(this->grid->grid[xCoord][yCoord]=="B");}
    else
    {
      return false;
    }
    
  }

  bool positionIsEmpty(int xCoord, int yCoord)
  {
    bool isWall=positionIsWall(xCoord,yCoord);
    bool isBattery =positionhasBattery(xCoord,yCoord);

    // return If the position does not have a wall or battery
    // reutrn if the position has a blank
    return((!isWall||!isBattery)||this->grid->grid[xCoord][yCoord]=="");

  }


  void moveRobot()
  {
    // If the sensor matches the position
     // Then move robot else default behaviour
  }
  
  void reproduction(Robot& parent1,Robot& parent2)
  {
    // splice genes from parent into child
  }

  void addGenesToRobot()
  {
    // Adds all 16 genes to the robot
    int geneSize=15;
    int index=0;
    while(index<genome->size())
    {        
        Gene* gene= new Gene(index);
        this->genome->set(index,gene);
        index++;  
    }
	} 

	void loadSensorToRobot()
  {
    // Adds Sensor
    int geneSize=15;
    int index=0;
    while(index<sensor->size())
    {
        Gene* gene= new Gene(index);
        this->sensor->set(index,gene);
        index++;  
    } 
  }







  void robotUnitTest()
  {
    Robot robot;
    cout<<robot;
  }

  friend ostream& operator <<(ostream& output,Robot& robot)
  {
    output<<"Robot Grid:\n"<<*robot.grid;
    output<<"Robot Health: "<<robot.health<<'\n';
    output<<"Lifespan: "<<robot.lifespan<<'\n';
    for(int i=0;i<robot.genome->size();i++)
    {
      output<<"Gene: "<<i+1<<'\n';
      output<<*robot.genome->get(i)<<'\n';
    }
    return output;
  }

  void populateGrid()
  {
    // Add a random number to grid

    RandomNumberGenerator rand; // random number functor
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
  

 
};


class Simulation
{
  public:

  Vector<Robot*>* population;


  Simulation()
  {
    population=new Vector<Robot*>(2);
    addRobots();
    runSimulation();
  }

  Simulation(int size)
  {
    population=new Vector<Robot*>(size);
    addRobots();
    runSimulation();
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
    
    // Run simulation for all robots
   
    cout<<"running simulation\n";
    for(int index=0;index<population->size();index++)
    {
        
      //runRobotThoughSimulation(*this->population->get(index));

  
    }
  }

  void runRobotThoughSimulation(Robot& robot)
  {
    
    int index;
    while(robot.health>0)
    {

      // make the robot run through the simulation as long as it is alive
      index++;
    }
  }

  
  void unitTests()
  {
    Simulation simulation(2);
    int index=0;
    cout<<"Simulation Unit Tests\n";
    
    while(index<simulation.population->size())
    {
      cout<<*simulation.population->get(index);
      index++;
    }
    

    
    
  }

};

// Function Prototypes
void UnitTests();
void ProgramGreeting();
int randomNumber();

int main()
{
  cout<<"Genetic Algorithm Robots\n";
  UnitTests();

}


void UnitTests()
{
  /*
  Gene gene(1);
  gene.GeneUnitTest();
  RandomNumberGenerator random;
  */
  //Grid grid;
  //grid.gridUnitTest();
  //Robot robot;
  //robot.robotUnitTest();
  
  Simulation simulation;
  simulation.unitTests();
}