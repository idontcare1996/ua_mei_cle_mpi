/*

TASK 1 - Creation of room configuration data files

*/

// IMPORTS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

// IGNORE UNUSED SCANF RETURNS
#pragma GCC diagnostic ignored "-Wunused-result"

// DEFINE FUNCTIONS FOR LATER USE
 #define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

// Input Functions

float GetFloat(bool positive);
long GetUpdateFrequency();
void AddCuboid(char ***nodes, float width, float depth, float height, float node_spacing);
void AddSphere(char ***nodes, float width, float depth, float height, float node_spacing, int X, int Y, int Z);
void AddElement(char ***nodes, float width, float depth, float height, float node_spacing,char *element);
void SaveRoom(char ***nodes, int X, int Y, int Z, long update_frequency);
int main ()
{
    // VARIABLES TO USE

    float width,depth,height; // Width, Depth, Height of the room to be modelled
    float new_width, new_depth, new_height; // Adjusted Width, Depth and Height
    int X,Y,Z;           // Array dimensions (in number of nodes)
    int sources = 0;        // Sound wave sources
    int receivers = 0;      // Sound wave receivers
    const int speed_of_sound = 344;      // Speed of sound in the medium (air) in m/s
    long update_frequency;  // Frequency update
    float node_spacing;     // Node spacing ( space between each and every node )

    int main_menu_option = -1;

    float x,x_min,x_max;    // Cuboid's X axis dimension and coordinates for start/end
    float y,y_min,y_max;    // Cuboid's Y axis dimension and coordinates for start/end
    float z,z_min,z_max;    // Cuboid's Z axis dimension and coordinates for start/end
    float abs_coefficient;  // Absortion coefficient

    char ***nodes;          // Node array


    // ASK FOR ROOM's DIMENSIONS

    printf(" Please enter array dimensions:\n");
    printf("\n Width: ");
    width = GetFloat(true);
    printf("\n Depth: ");
    depth = GetFloat(true);
    printf("\n Height: ");
    height = GetFloat(true);
    printf("\n Dimensions W,D,H(m) : %f,%f,%f \n ",width,depth,height);
    printf("\n Volume (m^3): %fm^3 \n",(width*depth*height));


    // ASK FOR MESH UPDATE FREQUENCY (fu)

    printf("\n \n Please enter the mesh update frequency: \n");
    update_frequency = GetUpdateFrequency();

    // CALCULATE NODE SPACING (d)
    printf("\n Calculating node spacing...");
    node_spacing = (speed_of_sound * sqrt(3)) / update_frequency;
    printf("\n Node spacing: %fm", node_spacing);

    // CALCULATE ARRAY DIMENSIONS

    printf("\n\n Calculation array dimensions (in number of nodes)...");
    X = (int) ceil(width / node_spacing);
    Y = (int) ceil(depth / node_spacing);
    Z = (int) ceil(height / node_spacing);
    printf("\n Array: X=%i Y=%i Z=%i", X,Y,Z);

    // CALCULATE ROOM SIZE AFTER ARRAY DIMENSIONS

    new_width = (node_spacing * X);
    new_depth = (node_spacing * Y);
    new_height = (node_spacing * Z);

    if(width!=new_width || depth!=new_depth || height != new_height)
    {    
        printf("\n\n Due to constraints, \n the room should now have: \n Width: %f(m) Depth: %f(m) Height: %f(m) ",new_width,new_depth,new_height);
        width = new_width; depth = new_depth; height = new_height;
    }
    // INITIALIZE THE ARRAY

    printf( "\n\n Initializing the array... \n\n");

    nodes[X][Y][Z];
    nodes = (char***) malloc(X * sizeof(char**));
    for (int x = 0; x <= X; x++)
    {
        nodes[x] = (char**) malloc(Y * sizeof (char*));
        for (int y = 0; y <= Y ; y++)
        {
            nodes[x][y] = (char*) malloc(Z * sizeof(char));
            for (int z = 0; z <= Z; z++)
            {
                nodes[x][y][z] = ' ';
            }
        }
    }

    // MAIN MENU

    do
    {
        printf("\n\n\n \tMENU \n\n");
        printf("1. Add Sphere\n");
        printf("2. Add Cuboid\n");
        printf("3. Add Source\n");
        printf("4. Add Receiver\n");
        printf("5. Save Configurations\n");
        printf("0. Exit\n");
        printf("Option: ");
        scanf("%d", &main_menu_option);
        switch (main_menu_option) {
        case 1:
            printf("\n SPHERE \n");
            AddSphere(nodes, width, depth, height, node_spacing,X,Y,Z);
            break;
        case 2:
            printf("\n CUBOID \n");
            AddCuboid(nodes, width, depth, height, node_spacing);
            break;
        case 3:
            printf("\n SOURCE \n");
            AddElement(nodes, width, depth, height, node_spacing,"source");
            sources++;
            break;
        case 4:
            printf("\n RECEIVER \n");
            AddElement(nodes, width, depth, height, node_spacing,"receiver");
            receivers++;
            break;
        case 5:
            printf("\n SAVE \n");
            if (sources >=1 && receivers >= 1)
            {   
                printf(" Saving... Please wait");
                SaveRoom(nodes, X, Y, Z, update_frequency);
            }
            else
            printf("It must be specified at least one source and one receiver\n"); 
            break;
        case 0:
            printf("Finishing program.\n");
            break;
        default:
            printf("Invalid option.\n");
            break;
        }
    }
    while(main_menu_option != 0);

    return 0;
}


float GetFloat(bool positive)
{
    if(positive == true)
    {   
        
        float numf;
        do
        {    
            while(scanf("%f",&numf) != 1 )
            {
                printf("\nERROR: Please enter a number... \n ");
                
                while(getchar() != '\n');
            }
            if (numf <= 0.0f)
            printf("ERROR: Please enter a positive number.\n");
        }
        while(numf <= 0.0f);
        
        return numf;
    }
    else
    {          
        float numf;
        do
        {    
            while(scanf("%f",&numf) != 1 )
            {
                printf("\nERROR: Please enter a number... \n ");
                
                while(getchar() != '\n');
            }
            if (numf < 0.0f)
            printf("ERROR: Please enter a positive number.\n");
        }
        while(numf < 0.0f);       
        return numf;
    }
}
long GetUpdateFrequency()
{
    int option;
    long frequency;
    do
    {        
        printf("1. 48000 Hz\n");
        printf("2. 44100 Hz\n");
        printf("3. 22050 Hz\n");
        printf("4. 16000 Hz\n");
        printf("5. 11025 Hz\n");
        printf("6. 8000 Hz\n");
        printf("Option: ");
        while(scanf("%d",&option) != 1)
        {
            printf("\nERROR: Please enter an integer... \n ");
            
            while(getchar() != '\n');
        }
        if (option < 1 || option > 6)
        printf("ERROR: Invalid option.\n");
    }
    while (option < 1 || option > 6);

    switch (option)
    {
        case 1:
        {
            frequency = 48000;
            break;
        }
        case 2:
        {
            frequency = 44100;
            break;
        }
        case 3:
        {
            frequency = 22050;
            break;
        }
        case 4:
        {
            frequency = 16000;
            break;
        }
        case 5:        
        {
            frequency = 11025;
            break;
        }
        case 6:        
        {
            frequency = 8000;
            break;
        }
    }
    return frequency;
}
void AddCuboid(char ***nodes, float width, float depth, float height, float node_spacing) {
    float   x_min = 0, x_max = 0,
            y_min = 0, y_max = 0,
            z_min = 0, z_max = 0;
    char abs_coefficient;
            
    printf("\n Please enter the lower and upper limits of the cuboid in each axis:\n");
    // X
    printf("\n X axis: \n");
    do
    {
        printf("Lower: ");
        scanf("%f", &x_min);
        if(x_min < 0 || x_min > width)
            printf(" Value must be within the 0-%f range... \n",width);       
    }
    while (x_min > width || x_min < 0);
    do
    {
        printf("Upper: ");
        scanf("%f", &x_max);
        if (x_max < x_min || x_max > width)
            printf(" Value must be within the %f-%f range... \n",x_min, width);
    }
    while (x_max < x_min || x_max > width);

   // Y
    printf("\n Y axis: \n");
    do
    {
        printf("Lower: ");
        scanf("%f", &y_min);
        if(y_min < 0 || y_min > depth)
            printf(" Value must be within the 0-%f range... \n",depth);       
    }
    while (y_min > depth|| y_min < 0);
    do
    {
        printf("Upper: ");
        scanf("%f", &y_max);
        if (y_max < y_min || y_max > depth)
            printf(" Value must be within the %f-%f range... \n",y_min, depth);
    }
    while (y_max < y_min || y_max > depth);
    

   // Z
    printf("\n Z axis: \n");
    do
    {
        printf("Lower: ");
        scanf("%f", &z_min);
        if(z_min < 0 || z_min > height)
            printf(" Value must be within the 0-%f range... \n",height);       
    }
    while (z_min > height || z_min < 0);
    do
    {
        printf("Upper: ");
        scanf("%f", &z_max);
        if (z_max < z_min || z_max > height)
            printf(" Value must be within the %f-%f range... \n",z_min, height);
    }
    while (z_max < z_min || z_max > height);


    // GET THE CUBOID'S ABSORTION COEFFICIENT
     do
    {
        printf("\n What's the absortion coefficient?");
        printf("A. Fully Absorptive (p = 0)\n");    printf("B. p = 0.1\n"); printf("C. p = 0.2\n");
        printf("D. p = 0.3\n");        printf("E. p = 0.4\n");        printf("F. p = 0.5\n");
        printf("G. p = 0.6\n");        printf("H. p = 0.7\n");        printf("I. p = 0.8\n");
        printf("J. p = 0.9\n");        printf("1. p = 0.91\n");        printf("2. p = 0.92\n");
        printf("3. p = 0.93\n");        printf("4. p = 0.94\n");        printf("5. p = 0.95\n");
        printf("6. p = 0.96\n");        printf("7. p = 0.97\n");        printf("8. p = 0.98\n");
        printf("9. p = 0.99\n");        printf("Z. Fully Reflective (p = 1)\n");
        printf("Option: ");
        getchar();
        scanf("%c", &abs_coefficient);
        //printf(" Absortion Coefficient: %c",abs_coefficient);
    }
        while  (abs_coefficient!='A' && abs_coefficient!='B' && abs_coefficient!='C' && 
                abs_coefficient!='D' && abs_coefficient!='E' && abs_coefficient!='F' && 
                abs_coefficient!='G' && abs_coefficient!='H' && abs_coefficient!='I' && 
                abs_coefficient!='J' && abs_coefficient!='1' && abs_coefficient!='2' && 
                abs_coefficient!='3' && abs_coefficient!='4' && abs_coefficient!='5' && 
                abs_coefficient!='6' && abs_coefficient!='7' && abs_coefficient!='8' && 
                abs_coefficient!='9' && abs_coefficient!='Z');

    

    
    // GET THE NUMBER OF NODES TO CHANGE IN EACH AXIS

    int i_min = (int) ceil( x_min / node_spacing); int i_max = (int) ceil( x_max / node_spacing);
    int j_min = (int) ceil( y_min / node_spacing); int j_max = (int) ceil( y_max / node_spacing);
    int k_min = (int) ceil( z_min / node_spacing); int k_max = (int) ceil( z_max / node_spacing);
    printf(" \n\n %i,%i %i,%i %i,%i \n\n",i_min,i_max,j_min,j_max,k_min,k_max);


    for (int a = i_min; a <= i_max; a++)
    {
        for (int b = j_min; b <= j_max; b++)
        {
            for (int c = k_min; c <= k_max; c++)
            {
                nodes[a][b][c] = abs_coefficient;
            }
        }
    }
    printf("\n Added cuboid...");
}
void AddSphere(char ***nodes, float width, float depth, float height, float node_spacing, int X, int Y, int Z)
{

    float sphere_x,sphere_y,sphere_z,radius;
    int sphere_node_x,sphere_node_y,sphere_node_z;
    int max_width,max_depth,max_height;

    char abs_coefficient;

    int cube_x_p,cube_x_n,
        cube_y_p,cube_y_n,
        cube_z_p,cube_z_n;
   
    // GET RADIUS    
    printf("\n\n Please enter the radius of the sphere: ");
    do
    {
        printf("\n Radius value: ");
        scanf("%f", &radius);
        if (radius < 0.0f)
            printf(" Radius must be bigger than 0");        
    }
    while (radius < 0.0f);
    
    printf("\n\n Please enter the center of the sphere: \n\n");

    printf("\n X value: ");
    do
    {   
        sphere_x = GetFloat(false);
        if( sphere_x > width)
            printf(" ERROR: Point distance can't be bigger than the width of the room (%f)", width);
    }
    while (sphere_x > width);

    printf("\n Y value: ");
    do
    {
        sphere_y = GetFloat(false);
        if( sphere_y > depth)
            printf(" ERROR: Point distance can't be bigger than the depth of the room (%f)", depth);
    }
    while (sphere_y > depth);

    printf("\n Z value: ");
    do
    {
        sphere_z = GetFloat(false);
        if( sphere_z > height)
            printf(" ERROR: Point distance can't be bigger than the height of the room (%f)", height);
    }
    while (sphere_z > height);


    // GET THE SPHERE'S ABSORTION COEFFICIENT
    do
    {
        printf("\n What's the absortion coefficient?");
        printf("A. Fully Absorptive (p = 0)\n");    printf("B. p = 0.1\n"); printf("C. p = 0.2\n");
        printf("D. p = 0.3\n");        printf("E. p = 0.4\n");        printf("F. p = 0.5\n");
        printf("G. p = 0.6\n");        printf("H. p = 0.7\n");        printf("I. p = 0.8\n");
        printf("J. p = 0.9\n");        printf("1. p = 0.91\n");        printf("2. p = 0.92\n");
        printf("3. p = 0.93\n");        printf("4. p = 0.94\n");        printf("5. p = 0.95\n");
        printf("6. p = 0.96\n");        printf("7. p = 0.97\n");        printf("8. p = 0.98\n");
        printf("9. p = 0.99\n");        printf("Z. Fully Reflective (p = 1)\n");
        printf("Option: ");
        getchar();
        scanf("%c", &abs_coefficient);
        
    }
    while  (abs_coefficient!='A' && abs_coefficient!='B' && abs_coefficient!='C' && 
            abs_coefficient!='D' && abs_coefficient!='E' && abs_coefficient!='F' && 
            abs_coefficient!='G' && abs_coefficient!='H' && abs_coefficient!='I' && 
            abs_coefficient!='J' && abs_coefficient!='1' && abs_coefficient!='2' && 
            abs_coefficient!='3' && abs_coefficient!='4' && abs_coefficient!='5' && 
            abs_coefficient!='6' && abs_coefficient!='7' && abs_coefficient!='8' && 
            abs_coefficient!='9' && abs_coefficient!='Z');


    // GET THE CENTER NODE
    sphere_node_x = (int) ceil( sphere_x / node_spacing );
    sphere_node_y = (int) ceil( sphere_y / node_spacing );
    sphere_node_z = (int) ceil( sphere_z / node_spacing );

    // GET NUMBER OF NODES THAT MAKE THE RADIUS
    int radius_node = ((int) ceil( (sphere_x+radius) / node_spacing)) - sphere_node_x;

    // DRAW A BOX AROUND THE SPHERE, TO AVOID SCANNING THE ENTIRE ROOM FOR NODES INSIDE SPHERE

    cube_x_p = sphere_node_x + radius_node ;    cube_x_n = sphere_node_x - radius_node ;
    cube_y_p = sphere_node_y + radius_node ;    cube_y_n = sphere_node_y - radius_node ;
    cube_z_p = sphere_node_z + radius_node ;    cube_z_n = sphere_node_z - radius_node ;

    max_width = (int) ceil( width / node_spacing );

    // CHECK WHICH NODES ARE INSIDE BOTH THE SPHERE AND THE ROOM AND ASSIGN THE COE

    for (int a = cube_x_n; a <= cube_x_p; a++)
    {
        for (int b = cube_y_n; b <= cube_y_p; b++)
        {
            for (int c = cube_z_n; c <= cube_z_p; c++)
            {
                if((pow((a-sphere_node_x),2)) +
                    (pow((b-sphere_node_y),2)) +
                    (pow((c-sphere_node_z),2)) <= pow(radius_node,2))
                    { 
                        if(a>=0 && a<X && b>=0 && b<Y && c>=0 && c<Z)
                        {
                            nodes[a][b][c] = abs_coefficient;
                        }
                    }
            }
        }
    }
    printf("\n Added sphere...");
}
void AddElement(char ***nodes, float width, float depth, float height, float node_spacing,char *element) {

    float x,y,z;
    int i,j,k;

    printf("\n\n Please enter location of the element: \n\n");

    printf("\n X value: ");
    do
    {   
        x = GetFloat(false);
        if( x > width)
            printf(" ERROR: Point distance can't be bigger than the width of the room (%f)", width);
    }
    while (x > width);

    printf("\n Y value: ");
    do
    {
        y = GetFloat(false);
        if( y > depth)
            printf(" ERROR: Point distance can't be bigger than the depth of the room (%f)", depth);
    }
    while (y > depth);

    printf("\n Z value: ");
    do
    {
        z = GetFloat(false);
        if( z > height)
            printf(" ERROR: Point distance can't be bigger than the height of the room (%f)", height);
    }
    while (z > height);

    i = (int) ceil( x / node_spacing );
    
    j = (int) ceil( y / node_spacing );
    
    k = (int) ceil( z / node_spacing );
    


    if (element == "source")
    {
        nodes[i][j][k] = 'S';
        printf("\n New Source Added at (%d, %d, %d)\n", i, j, k);
    }
    else if (element == "receiver")
    {
        nodes[i][j][k] = 'R';
        printf("\n New Receiver Added at (%d, %d, %d)\n", i, j, k);
    }
}
void SaveRoom(char ***nodes, int X, int Y, int Z, long update_frequency) {
    FILE *file = fopen("room-config.dwm", "w");
    double number = 0;
    printf(" Saving %d Bytes to \"room-config.dwm\" ", (X*Y*Z));
    
    fprintf(file, "%d %d %d %ld\n", X, Y, Z, update_frequency);
    for (int i = 0; i < X; i++)
    {
        for (int j = 0; j < Y; j++)
        {
            for (int k = 0; k < Z; k++)
            {
                fprintf(file, "%c", nodes[i][j][k]);
                number++;
            }
        }
    }
    fclose(file);
    printf(" \n\n Number of nodes: %lf\n", number);
    printf("File Saved\n");
}