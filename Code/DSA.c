#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define NUM_RESOURCES 11

typedef struct {
    char name[50];
    int urgency; // Higher urgency values indicate more critical conditions
} Patient;

typedef struct {
    Patient* heapArray;
    int capacity;
    int size;
} MaxHeap;


MaxHeap createMaxHeap(int capacity) {
    MaxHeap heap;
    heap.heapArray = (Patient*)malloc(sizeof(Patient) * (capacity + 1)); // +1 for 1-based indexing
    heap.capacity = capacity;
    heap.size = 0;
    return heap;
}


void swap(Patient* a, Patient* b) {
    Patient temp = *a;
    *a = *b;
    *b = temp;
}


void heapifyUp(MaxHeap* heap, int index) {
    while (index > 1 && heap->heapArray[index].urgency > heap->heapArray[index / 2].urgency) {
        swap(&heap->heapArray[index], &heap->heapArray[index / 2]);
        index = index / 2;
    }
}

void enqueue(MaxHeap* heap, Patient patient[], int capacity) {
    if (heap->size == heap->capacity) {
        printf("Heap is full. Cannot enqueue more patients.\n");
        return;
    }
    for(int i=0; i<capacity; i++)
    {
       heap->size++;
       heap->heapArray[heap->size] = patient[i];
       heapifyUp(heap, heap->size);
    }
}


void heapifyDown(MaxHeap* heap, int index) {
    int maxIndex = index;
    int leftChild = 2 * index;
    int rightChild = 2 * index + 1;

    if (leftChild <= heap->size && heap->heapArray[leftChild].urgency > heap->heapArray[maxIndex].urgency) {
        maxIndex = leftChild;
    }

    if (rightChild <= heap->size && heap->heapArray[rightChild].urgency > heap->heapArray[maxIndex].urgency) {
        maxIndex = rightChild;
    }

    if (index != maxIndex) {
        swap(&heap->heapArray[index], &heap->heapArray[maxIndex]);
        heapifyDown(heap, maxIndex);
    }
}


Patient dequeue(MaxHeap* heap) {
    if (heap->size == 0) {
        Patient emptyPatient = {"", 0};
        return emptyPatient;
    }

    Patient root = heap->heapArray[1];
    heap->heapArray[1] = heap->heapArray[heap->size];
    heap->size--;

    heapifyDown(heap, 1);

    return root;
}


void printHeap(MaxHeap* heap) {
    printf("\nEmergency Room Heap:\n");
    for (int i = 1; i <= heap->size; i++) {
        printf("Patient: %s, Urgency: %d\n", heap->heapArray[i].name, heap->heapArray[i].urgency);
    }
}

/////////////

typedef struct {
    int resourceID;
    bool isAvailable;
} Resource;

typedef struct {
    Resource resources[NUM_RESOURCES];
} ResourceManager;


void initializeResources(ResourceManager* manager) {
    for (int i = 1; i < NUM_RESOURCES; i++) {
        manager->resources[i].resourceID = i;
        manager->resources[i].isAvailable = true;
    }
}


bool allocateResource(ResourceManager* manager, int resourceID) {
    if (resourceID < 0 || resourceID >= NUM_RESOURCES) {
        printf("Invalid resource ID\n");
        return false;
    }

    if (manager->resources[resourceID].isAvailable) {
        manager->resources[resourceID].isAvailable = false;
        printf("Resource %d allocated.\n", resourceID);
        return true;
    } else {
        printf("Resource %d is not available.\n", resourceID);
        return false;
    }
}


void deallocateResource(ResourceManager* manager, int resourceID) {
    if (resourceID < 0 || resourceID >= NUM_RESOURCES) {
        printf("Invalid resource ID\n");
        return;
    }

    if(manager->resources[resourceID].isAvailable != true)
    {
       manager->resources[resourceID].isAvailable = true;
       printf("Resource %d deallocated.\n", resourceID);
    }
    else
    {
        printf("\nThe resource %d is already available", resourceID);
    }
}    


void printResource(ResourceManager* manager)
{
    for(int i=1; i< NUM_RESOURCES; i++)
    {
        if(manager->resources[i].isAvailable==true)
        {
            printf("%d\n",manager->resources[i].resourceID);
        }
    }
}

////////////////

typedef struct
{
    int did;
    char name[50];
}Doctors;


int linearsearch_doctors(Doctors doctors[], int n, char search_name[])
{
    for(int i=0; i<n; i++)
    {
        if(strcmp(doctors[i].name,search_name)==0)
        {
            return i;
        }
    }
    return -1;
} 


void printDoctors(Doctors doctors)
{
    printf("NAME:%s \nID:%d",doctors.name,doctors.did);
}

////////////

typedef struct {
    double temperature;  
    double humidity;     
    int No_of_patients;  
} DataPoint;

typedef struct {
    double weightTemperature;
    double weightHumidity;
    double bias;
} Model;


void normalizeData(DataPoint* data, int dataSize) {
    double maxTemp = 0.0;
    double maxHumidity = 0.0;

    for (int i = 0; i < dataSize; ++i) {
        if (data[i].temperature > maxTemp) {
            maxTemp = data[i].temperature;
        }
        if (data[i].humidity > maxHumidity) {
            maxHumidity = data[i].humidity;
        }
    }

    for (int i = 0; i < dataSize; ++i) {
        data[i].temperature /= maxTemp;
        data[i].humidity /= maxHumidity;
    }
}

Model trainModel(DataPoint* data, int dataSize, double learningRate, int epochs) {
    Model model = {0.0, 0.0, 0.0};


    normalizeData(data, dataSize);

    for (int epoch = 0; epoch < epochs; ++epoch) {
        double tempSum = 0.0;
        double humidSum = 0.0;
        double biasSum = 0.0;

        for (int i = 0; i < dataSize; ++i) {
            double prediction = model.weightTemperature * data[i].temperature +
                                model.weightHumidity * data[i].humidity +
                                model.bias;
            double error = prediction - data[i].No_of_patients;

            tempSum += error * data[i].temperature;
            humidSum += error * data[i].humidity;
            biasSum += error;
        }

        model.weightTemperature -= learningRate * (2.0 / dataSize) * tempSum; 
        model.weightHumidity -= learningRate * (2.0 / dataSize) * humidSum;    
        model.bias -= learningRate * (2.0 / dataSize) * biasSum;               
    }

    return model;
}

double predictPatientCount(Model model, double temperature, double humidity) {
    
    temperature /= 100.0; 
    humidity /= 100.0;   

    return model.weightTemperature * temperature + model.weightHumidity * humidity + model.bias;
}

///////////////

int partition (Patient patient[],int l, int r)
{
    
    int i, j;

    Patient pivot = patient[l];

    i = l;
    j = r + 1;

    while(1)
    {
        do
        {
            i++;

        }while(strcmp(patient[i].name, pivot.name) < 0 && i<=r);


        do
        {
            j--;

        }while(strcmp(patient[j].name, pivot.name) > 0);

        if(i >= j)
        {
            break;
        }

        Patient temp = patient[i];
        patient[i] = patient[j];
        patient[j] = temp;
    }

    Patient temp = patient[l];
    patient[l] = patient[j];
    patient[j] = temp;

    return j;
}


void quicksort(Patient patient[], int l, int r)
{
    if(l<r)
    {
        int s = partition(patient,l,r);
        quicksort(patient, l, s-1);
        quicksort(patient, s+1, r);
    }
}

void patientsorting(Patient patient[], int capacity)
{
    for(int i=0 ; i < capacity; i++)
    {
        printf("NAME %d : %s\n" ,i+1 ,patient[i].name);
    }
}

//////////////


typedef struct {
    char name[50];

} Node;

typedef struct {
    int weight;

} Edge;


typedef struct {
    Node *nodes;
    Edge **edges;
    int numNodes;
} Graph;


Graph* createGraph(int numNodes) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = numNodes;
    graph->nodes = (Node*)malloc(numNodes * sizeof(Node));
    graph->edges = (Edge*)malloc(numNodes * sizeof(Edge));

    for (int i = 0; i < numNodes; ++i) {
        printf("\nEnter the name of the department %d:",i);
        scanf("%s", graph->nodes[i].name);
        graph->edges[i] = (Edge*)malloc(numNodes * sizeof(Edge));

        for (int j = 0; j < numNodes; ++j) {
            graph->edges[i][j].weight = INT_MAX;
        }
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    graph->edges[src][dest].weight = weight;
}

void addEdge1(Graph* graph, int src, int dest, int weight) {
    graph->edges[src][dest].weight = weight;
    graph->edges[dest][src].weight = weight;
}


int minDistance(int dist[], int sptSet[], int numNodes) {
    int min = INT_MAX, minIndex;

    for (int v = 0; v < numNodes; v++) {
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void printShortestPath(Graph* graph, int parent[], int j) {
    if (parent[j] == -1) {
        printf("%s ", graph->nodes[j].name);
        return;
    }

    printShortestPath(graph, parent, parent[j]);
    printf("%s ", graph->nodes[j].name);
}

void dijkstra(Graph* graph, int src, int dest) {
    int numNodes = graph->numNodes;
    int dist[numNodes];     // Distance from source to node i
    int sptSet[numNodes];   // Shortest path tree set
    int parent[numNodes];    // Parent array to store the shortest path tree

    for (int i = 0; i < numNodes; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    dist[src] = 0;

    for (int count = 0; count < numNodes - 1; count++) {
        int u = minDistance(dist, sptSet, numNodes);
        sptSet[u] = 1;

        for (int v = 0; v < numNodes; v++) {
            if (!sptSet[v] && graph->edges[u][v].weight != INT_MAX &&
                dist[u] != INT_MAX &&
                dist[u] + graph->edges[u][v].weight < dist[v]) {
                dist[v] = dist[u] + graph->edges[u][v].weight;
                parent[v] = u;
            }
        }
    }

    printf("\nShortest Path from %s to %s: ", graph->nodes[src].name, graph->nodes[dest].name);
    printShortestPath(graph, parent, dest);
    printf("\nShortest Distance: %d\n", dist[dest]);
}

int main() {
    int capacity;
    int resourceID;
    int count=0;
    int ndoc;
    char search_name[50];
    int numNodes;
    int src, dest;

    printf("Enter the number of departments: ");
    scanf("%d", &numNodes);

    // Create a graph with the specified number of departments
    Graph* graph = createGraph(numNodes);

    int opt = 0;
    printf("\nEnter \n1. For directed graph \n2. For undirected graph \nchoice:");
    scanf("%d", &opt);

    // Add edges to the graph
    if (opt == 1) {
        addEdge(graph, 0, 1, 1);
        addEdge(graph, 1, 2, 3);
        addEdge(graph, 2, 4, 2);
        addEdge(graph, 4, 3, 1);
        addEdge(graph, 3, 0, 5);
    }
    else if (opt == 2) {
        addEdge1(graph, 0, 1, 1);
        addEdge1(graph, 1, 2, 3);
        addEdge1(graph, 2, 4, 2);
        addEdge1(graph, 4, 3, 1);
        addEdge1(graph, 3, 0, 5);
    }



    printf("\nEnter the number of Doctor's in the hospital :");
    scanf("%d",&ndoc);

    Doctors doctors[ndoc];

    for(int i=0; i<ndoc; i++)
    {
        printf("\nEnter the Doctor's %d ID:",i+1);
        scanf("%d",&(doctors[i].did));
        printf("Enter the Doctor's %d NAME:",i+1);
        scanf("%s",doctors[i].name);
    }

    printf("\nEnter the capacity of the Emergency Room Heap for Patient's: ");
    scanf("%d", &capacity);

    MaxHeap emergencyRoomHeap = createMaxHeap(capacity);

    Patient patient[capacity];

    printf("Enter patient information:\n");
    for (int i = 0; i < capacity; ++i) {
    
        printf("\nPatient %d:\n", i + 1);
        printf("Name: ");
        scanf("%s", patient[i].name);
        printf("Urgency: ");
        scanf("%d", &patient[i].urgency);

    }

    enqueue(&emergencyRoomHeap, patient, capacity);

    printHeap(&emergencyRoomHeap);

    ResourceManager resourceManager;
    initializeResources(&resourceManager);

    printf("\nTreating patients:\n");
    while (emergencyRoomHeap.size > 0) {
        Patient patient = dequeue(&emergencyRoomHeap);
        printf("\nTreating patient: %s, Urgency: %d\n", patient.name, patient.urgency);

        printf("\nEnter the source department (0 to %d): ", numNodes - 1);
        scanf("%d", &src);
        printf("Enter the destination department (0 to %d): ", numNodes - 1);
        scanf("%d", &dest);

        if (src < 0 || src >= numNodes || dest < 0 || dest >= numNodes) {
            printf("Invalid source or destination department.\n");
        }
        else {

            dijkstra(graph, src, dest);
        }

        printf("Enter the resource ID to allocate the patient %s: ",patient.name);
        scanf("%d", &resourceID);                                                       //Any resource from 1 to 10
        allocateResource(&resourceManager, resourceID);
        count++;
    }
    

    printf("\nThe remaining resoruces that aren't allocated");
    printf("\n");
    printResource(&resourceManager);                                                    //printing the available resources after allocating the patients
    
    printf("\nDeallocation of the resources once the patient is treated");

    while(count!=0)
    {
        printf("\n\nEnter the resource ID to deallocate: ");
        scanf("%d", &resourceID);
        deallocateResource(&resourceManager, resourceID);
        count--;
    }
    
    printf("\n\nThe remaining resoruces after deallocation");
    printf("\n");
    printResource(&resourceManager); 

    printf("\nEnter the name of the doctor to be searched:");
    scanf("%s",search_name);
    int doctorindex=linearsearch_doctors(doctors,ndoc,search_name);

    if(doctorindex != -1)
    {
        printf("\nDoctor found");
        printf("\n");
        printDoctors(doctors[doctorindex]);
    }
    else
    {
        printf("\nDoctor not found");
    }


    printf("\n\nThe names of the patient's BEFORE SORTING:\n");
    patientsorting(patient,capacity);

    quicksort(patient, 0, capacity-1);

    printf("\nThe names of the patient's AFTER SORTING:\n");
    patientsorting(patient,capacity);


    DataPoint data[] = {
        {20.0, 60.0, 50},
        {25.0, 70.0, 50},
        {26.0, 77.0, 55},
        {28.0, 79.0, 55},
        {30.0, 81.0, 58},
        {32.0, 81.0, 58},
        {34.0, 82.0, 60},
        {34.0, 83.0, 61},
        {35.0, 85.0, 64},
        {35.0, 85.0, 64},
        {36.0, 85.0, 67},
        {37.0, 90.0, 69},
        {37.0, 95.0, 71},
        {38.0, 95.0, 73},
    };
    int dataSize = sizeof(data) / sizeof(data[0]);

    double learningRate = 0.01;
    int epochs = 10000;
    Model trainedModel = trainModel(data, dataSize, learningRate, epochs);


    double newTemperature = 28.0;
    double newHumidity = 65.0;
    double predictedPatientCount = predictPatientCount(trainedModel, newTemperature, newHumidity);

    printf("\n\nPredicted No Of Patients Arriving: %.2f\n", predictedPatientCount);

    free(emergencyRoomHeap.heapArray);
    free(graph->nodes);
    for (int i = 0; i < graph->numNodes; ++i) {
        free(graph->edges[i]);
    }
    free(graph->edges);
    free(graph);

return 0;
}