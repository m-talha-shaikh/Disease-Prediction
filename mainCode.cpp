#include <iostream>
#include <bits/stdc++.h>
#include <fstream>
#include <cstring>
#include <sstream>
#include "ui.h"
using namespace std;

void createBodyPartsList(void);
void createSymptomsList(void);
void createDiseasesList(void);
void createDiseasesWithSymptomsList(void);
void createSymptomsAdjList(void);
void createDiseasesAdjList(void);
void createDiseasesWithMedicationsList(void);
vector < pair <int,string> > bodyPartsVec;
vector < pair <int,string> > diseasesVec;
vector < pair <int,string> > symptomsVec;
vector < pair <int,int> > diseaseCountVec;
void vectorOfBodyParts(void);
void vectorOfDiseases(void);
void vectorOfSymptoms(void);
void vectorOfDiseaseCount(void);
void createGraph();
void medicationsForDiagnosedDisease(string);
void symptomsForDiagnosedDisease(string);
void createAllListAndFiles();
void predict();
void medicineLookup();
void symptomLookup();
void mergeSort(vector <pair <int, string> > &, vector <pair <int, string> > &, vector <pair <int, string> > &);
void sort(vector <pair <int, string> > &);
void sortForDiseasesVec();
void sortForbodyPartsVec();
void sortForsymptomsVec();
void diseaseDescription();

class Graph
{
public:
	map<int, bool> visited;
	map<int, list<int> > adj;
	void addEdge(int v, int w);
	void BFS(int v);
};

class Node
{
    public:
        string disease;
        char medications[5000];
        Node *left;
        Node *right;
        
        Node(string d, char* med){
            disease = d;
            strcpy(medications, med);
            left = right = NULL;
        }
};

class AVL
{
    public:
        Node *root;

        AVL(){
            root = NULL;
        }

        int height(Node*);
        int getBalanceFactor(Node*);
        Node *leftRotate(Node*);
        Node *rightRotate(Node*);
        Node *insert(Node*, string, char*);
        Node* insertFromFile(Node*);		        
		Node* search(Node* , string);
};

class BSTNode
{
    public:
        string disease;
        char symptoms[5000];
        BSTNode *left;
        BSTNode *right;
        
        BSTNode(string d, char* med){
            disease = d;
            strcpy(symptoms, med);
            left = right = NULL;
        }
};

class BST{
    public:
        BSTNode *root;

        BST()
		{
            root = NULL;
        }
        
        BSTNode* insertFromFile(BSTNode*);
        BSTNode* insert(BSTNode*, string, char*);
		BSTNode* BSTNodeSearch(BSTNode*, string);
};

Graph g;
int v1 = 9000; //root
vector<int> g1;

int main(){
	//create all files and list and graph
	createAllListAndFiles();
	
	int menuChoice;
    while (1)
    {
        system("cls");
        menuChoice = mainMenu();
        switch (menuChoice)
        {
        case 1:
            system("cls");
            system("title Disease Prediction");
            loadingAnimation();
            predict();
            break;
        case 2:
            system("cls");
            system("title Medicine Lookup");
            loadingAnimation();
            medicineLookup();
            break;
        case 3:
            system("cls");
            system("title Symptoms Lookup");
            loadingAnimation();
            symptomLookup();
            break;
        case 4:
            system("cls");
            system("title Diseases Description");
            loadingAnimation();
            diseaseDescription();
            break;
        case 5:
            system("cls");
            system("title About Us");
            loadingAnimation();
            aboutUs();
            break;
        case 6:
            system("cls");
            system("title System Policy");
            loadingAnimation();
            systemPolicy();
            break;
        case 7:
            system("cls");
            CursorPosition(40, 10);
            system("title Exit");
            loadingAnimation();
            exitNote();
            Sleep(2000);
            TextColor(7);
            exit(0);
            break;
        default:
            system("cls");
            system("title ERROR :(");
            CursorPosition(0, 0);
            system("color 4F");
            cout << "Wrong choice entered, try again!";
            Beep(1000, 300);
            Sleep(2000);
            system("color 0F");
            break;
        }
    }
	
	return 0;
}


//create all files, list and graph as well

void createAllListAndFiles()
{
	//Body Parts List
	createBodyPartsList();
	//Symptoms List
	createSymptomsList();
	//Diseases List
	createDiseasesList();
	//Diseases With Symptoms
	createDiseasesWithSymptomsList();
	//Adjacency List of Symptoms
	createSymptomsAdjList();
	//Vector Of BodyParts
 	vectorOfBodyParts();
 	//Vector Of Diseases
	vectorOfDiseases();
	//Vector Of Symptoms
	vectorOfSymptoms();
	//Vector Of Disease Count
	vectorOfDiseaseCount();
	//Adjacency List of Diseases
	createDiseasesAdjList();
	//Create Diseases With Medicines
	createDiseasesWithMedicationsList();
	//Create Graph
	createGraph();
	
	//sorting vectors
	sortForDiseasesVec();
	sortForbodyPartsVec();
	sortForsymptomsVec();
}

//Body Parts List
void createBodyPartsList(){
		int a;
	char b;
	char c[50];
	ifstream fin;
	ofstream fout;
	fin.open("./files/B)grouped-symptoms.txt");
	fout.open("./files/F)body-parts-list.txt");
	
	fin >> a;
	fout << a;
	b = fin.get();
	fout << b;
	fin.getline(c,100);
	fout << c << endl;	
	
	while(!fin.eof()){
		fin >> a;
		if(a < 11000){
			if(fin.eof()){
			break;
		}
			b=fin.get();
			if(fin.eof()){
			break;
		}
			fin.getline(c,100);
		}
		else{
			fout << a;
			if(fin.eof()){
			break;
		}
			b = fin.get();
			if(fin.eof()){
			break;
		}
			fout << b;
			if(fin.eof()){
			break;
		}
			fin.getline(c,100);
			fout << c << endl;	
		}
		if(fin.eof()){
			break;
		}
	}

	fin.close();
	fout.close();
}


//Symptoms List

void createSymptomsList(){
		int a;
	char b;
	char c[50];
	ifstream fin;
	ofstream fout;
	fin.open("./files/B)grouped-symptoms.txt");
	fout.open("./files/H)symptoms-list.txt");
	
	fin >> a;
	b = fin.get();
	fin.getline(c,100);
	
	while(!fin.eof()){
		fin >> a;
		if(fin.eof()){
			break;
		}
		if(a > 11000){
			b=fin.get();
			fin.getline(c,100);
		}
		else{
			fout << a;
			b = fin.get();
			fout << b;
			fin.getline(c,100);
			fout << c << endl;	
		}
		if(fin.eof()){
			break;
		}
	}

	fin.close();
	fout.close();
}


//Diseases List

void createDiseasesList(){
	int a;
	char b;
	char c[2500];
	ifstream fin;
	ofstream fout;
	fin.open("./files/I)raw-diseases.txt");
	fout.open("./files/K)diseaes-list.txt");
	
	fin >> a;	
	fout << a + 12000 << "-";
	b = fin.get();
	fin.getline(c,2000,9); //9 ASCII CODE FOR TAB
	fout << c << endl;
	b = fin.get();
	while(b != '\n'){
		b = fin.get();
	}
	
	while(!fin.eof()){
		fin >> a;	
		fout << a + 12000 << "-";
		if(fin.eof()){
			break;
		}
		b = fin.get();
		if(fin.eof()){
			break;
		}
		fin.getline(c,2000,9);	//9 ASCII CODE FOR TAB
		fout << c << endl;
		if(fin.eof()){
			break;
		}
		b = fin.get();
		if(fin.eof()){
			break;
		}
		while(b != '\n'){
			if(fin.eof()){
			break;
			}
			b = fin.get();
		}
		if(fin.eof()){
			break;
		}
	}
	
	fin.close();
	fout.close();
}

void createDiseasesWithSymptomsList(){
    ifstream fin;
	fin.open("./files/I)raw-diseases.txt");
	ofstream fout;
	fout.open("./files/L)Disease-Sym.txt");
	
	int id;
	char disease[200];
	char extra[5000];
	char e;
	
	while(!fin.eof()){
		
		fin >> id;
		fout << id+12000;
		fin.getline(extra,5000,'{');
		e = fin.get();
		e = fin.get();
		
		int i = 0;
		while(1){	
			fin.getline(disease,200,'-');
			if(disease[0] == 34){
				break;
			}
			fout << "-" << disease;
		}
		fin.getline(extra,5000,'\n');
		fout << "-!-" << endl;
	}
	fout << 0;
	fin.close();
	fout.close();
}


//Adjacency List of Symptoms

void createSymptomsAdjList(){
	int a;
	char b;
	char c[50];
	ifstream fin;
	ofstream fout;
	fin.open("./files/B)grouped-symptoms.txt");
	fout.open("./files/D)symptoms-adjacency-list.txt");
	fin >> a;
	fout << a;
	b = fin.get();
	while(b != '\n'){
		b = fin.get();
	}
	while(!fin.eof()){
		fin >> a;
		if(a < 11000){
			fout << "-" << a;
		}
		else{
			fout << endl;
			fout << a;
		}
		if(fin.eof()){
			break;
		}
		b = fin.get();
		while(b != '\n'){
			b = fin.get();
		}
		if(fin.eof()){
			break;
		}
	}
	fin.close();
	fout.close();
}

//Vector Of BodyParts
void vectorOfBodyParts(){
	ifstream fin;
	fin.open("./files/F)body-parts-list.txt");
	
	int id;
	char a;
	char part[100];
	
	fin >> id;
	a = fin.get();
	fin.getline(part,100);
	
	bodyPartsVec.push_back(make_pair(id,part));
	
	while(!fin.eof()){
		if(fin.eof()) break;
		fin >> id;
		if(fin.eof()) break;
		a = fin.get();
		if(fin.eof()) break;
		fin.getline(part,100);
		bodyPartsVec.push_back(make_pair(id,part));
	}
	   
    fin.close();	
}

//Vector Of Diseases
void vectorOfDiseases(void){
	ifstream fin;
	fin.open("./files/K)diseaes-list.txt");
	
	int id;
	char a;
	char disease[100];
	
	fin >> id;
	a = fin.get();
	fin.getline(disease,100);
	
	diseasesVec.push_back(make_pair(id,disease));
	
	while(!fin.eof()){
		if(fin.eof()) break;
		fin >> id;
		if(fin.eof()) break;
		a = fin.get();
		if(fin.eof()) break;
		fin.getline(disease,100);
		diseasesVec.push_back(make_pair(id,disease));
	}
	   
    fin.close();
}


void vectorOfDiseaseCount(void){
	for(int i = 0 ; i < diseasesVec.size(); i++){
		diseaseCountVec.push_back(make_pair(diseasesVec[i].first,0));
	}
}



//Vector Of Symptoms
void vectorOfSymptoms(){
	ifstream fin;
	fin.open("./files/H)symptoms-list.txt");
	
	int id;
	char a;
	char symptom[100];
	
	fin >> id;
	a = fin.get();
	fin.getline(symptom,100);
	
	symptomsVec.push_back(make_pair(id,symptom));
	
	while(!fin.eof()){
		if(fin.eof()) break;
		fin >> id;
		if(fin.eof()) break;
		a = fin.get();
		if(fin.eof()) break;
		fin.getline(symptom,100);
		symptomsVec.push_back(make_pair(id,symptom));
	}
	   
    fin.close();
}

//Adjacency List of Diseases

void createDiseasesAdjList(){
	ifstream fin2;
	fin2.open("./files/L)Disease-Sym.txt");
	
	ofstream fout;
	fout.open("./files/M)Diseases-Adj-List.txt");
	
	int id2;
	int id3;
	char b;
	char sym2[200];
		
	while(!fin2.eof()){
		fin2 >> id2;
		if(id2 == 0) break;
		fout << id2;
		b = fin2.get();
		while(1){
			fin2.getline(sym2,200,'-');

			if(sym2[0] == '!') break;
			for(int i =0;i<symptomsVec.size();i++){
	        if(symptomsVec[i].second == sym2){
	        	id3 = symptomsVec[i].first;
				}
	    	}
	    	 fout << "-" << id3;
		}
		fout << endl;
		if(fin2.eof()) break;	
	}
}


//Diseases With Medications
void createDiseasesWithMedicationsList(){
	ifstream fin;
	fin.open("./files/I)raw-diseases.txt");
	ofstream fout;
	fout.open("./files/J)Disease-Med.txt");
	
	int id;
	char disease[200];
	char medications[200];
	char extra[5000];
	char e;
	
	while(!fin.eof()){
		
		fin >> id;
		fin.getline(disease, 200, '"');
		fout << disease <<"-";
		fin.getline(extra,5000,']');
		fin.getline(extra,5000, '{');
		e = fin.get();
		e = fin.get();
		
		int i = 0;
		while(1){	
			fin.getline(medications,200,'-');
			if(medications[0] == 34){
				break;
			}
			fout << medications << "-";
		}
		fin.getline(extra,5000,'\n');
		fout << "!-" << endl;
	}
	fout << '\n';
	fin.close();
	fout.close();
	
	ifstream fin2;
	fin2.open("./files/J)Disease-Med.txt");
	ofstream fout2;
	fout2.open("./files/S)Disease-Med.txt");
	if(fin2.is_open()){
		while(!fin2.eof()){
			e = fin2.get();
			if(e != 9){
				fout2 << e;
			}
		}
	}
	fout2 << '\n';
	fin2.close();
	fout2.close();
	
	remove("./files/J)Disease-Med.txt");
	rename("./files/S)Disease-Med.txt","./files/J)Disease-Med.txt");

}


//check

//InterPolation Search
void check(int v){
	int start = 0;
	int end = diseaseCountVec.size()-1;
	int key = v;
   int dist, valRange, indexRange, estimate;
   float fraction;
   while(start <= end && key >= diseaseCountVec[start].first && key <= diseaseCountVec[end].first) {
      dist = key - diseaseCountVec[start].first;
      valRange = diseaseCountVec[end].first - diseaseCountVec[start].first;     //range of value
      fraction = dist / valRange;
      indexRange = end - start;
      estimate = start + (fraction * indexRange);      //estimated position of the key
      if(diseaseCountVec[estimate].first == key)
         diseaseCountVec[estimate].second += 1;
      if(diseaseCountVec[estimate].first < key)
         start = estimate +1;
      else
         end = estimate - 1;
   }	
}


//Found

bool found(int v){
	for(int i = 0 ; i < g1.size() ; i++){
		if(v == g1[i]){
			return 1;
		}
	}
	return 0;
}


//Graph Functions

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
}
 
void Graph::BFS(int v)
{
	static int q = 0;
    visited[v] = true;
    check(v);
    if(v != 9000 || v < 12000)
	{
    	if(v < 11000)
		{
			//BINARY SEARCH
    		int low = 0;
			int high = symptomsVec.size() - 1;
			while (low <= high) {
				    int mid = low + (high - low) / 2;
				
				    if (symptomsVec[mid].first == v){
				    	{
			        if(q%2 == 0){	
			        	cout << v << " " << symptomsVec[mid].second; 
			        	int len = 50 - symptomsVec[mid].second.size();
			        	while(len != 0){
			        		cout << " ";
			        		len -= 1;
						}
					}
					else{
						cout << v << " " << symptomsVec[mid].second << endl;
					}
					q += 1;
	   				break;
    	        }
					}
				      
				
				    if (symptomsVec[mid].first < v)
				      low = mid + 1;
				
				    else
				      high = mid - 1;
  			}			
		}
		
		else if(v < 12000)
		{
			//BINARY SEARCH
			int low = 0;
			int high = bodyPartsVec.size() - 1;
			while (low <= high) {
				    int mid = low + (high - low) / 2;
				
				    if (bodyPartsVec[mid].first == v){
				    	{
			        if(q%2 == 0){	
			        	cout << v << " " << bodyPartsVec[mid].second; 
			        	int len = 50 - bodyPartsVec[mid].second.size();
			        	while(len != 0){
			        		cout << " ";
			        		len -= 1;
						}
					}
					else{
						cout << v << " " << bodyPartsVec[mid].second << endl;
					}
					q += 1;
	   				break;
    	        }
					}
				      
				
				    if (bodyPartsVec[mid].first < v)
				      low = mid + 1;
				
				    else
				      high = mid - 1;
  			}
		}
	}
	
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i){
        if (found(v))
		{
            BFS(*i);
        }
    }
}


void createGraph(){
		for(int i =0;i<bodyPartsVec.size();i++){
	   g.addEdge(v1,bodyPartsVec[i].first);
	}
	
	ifstream fin11;
	fin11.open("./files/D)symptoms-adjacency-list.txt");
	while(!fin11.eof()){
		int v3;
		int v4;
		if(fin11.eof()) break;
		fin11 >> v3;
		char a;
		if(fin11.eof()) break;
		a = fin11.get();
		while(a != '\n'){
			if(fin11.eof()) break;
			fin11 >> v4;
			g.addEdge(v3,v4);
			if(fin11.eof()) break;
			a = fin11.get();	
		}
		if(fin11.eof()) break;
	}
	fin11.close();
	
	ifstream fin12;
	fin12.open("./files/M)Diseases-Adj-List.txt");
	while(!fin12.eof()){
		int v3;
		int v4;
		if(fin12.eof()) break;
		fin12 >> v4;
		char a;
		if(fin12.eof()) break;
		a = fin12.get();
		while(a != '\n'){
			if(fin12.eof()) break;
			fin12 >> v3;
			g.addEdge(v3,v4);
			if(fin12.eof()) break;
			a = fin12.get();	
		}
		if(fin12.eof()) break;
	}
	fin12.close();
}

// AVL functions

int AVL::height(Node* root)
{
    if(root==NULL){
        return 0;
    }
    
    int left = height(root->left);
    int right = height(root->right);

    int h = max(left, right) + 1;
    
    return h;
}

int AVL::getBalanceFactor(Node *r)
{
    if(r == NULL)
	{
        return -1;
    }
    
    return(height(r->left) - height(r->right));
}

Node* AVL::leftRotate(Node *r)
{
    Node *x = r->right;
    Node *temp = x->left;

    x->left = r;
    r->right = temp;

    return x;
}

Node* AVL::rightRotate(Node *r)
{
    Node *x = r->left;
    Node *temp = x->right;

    x->right = r;
    r->left = temp;

    return x;
}

Node* AVL::insertFromFile(Node *r)
{
    char disease[500];
    char extra[5000];
	char e;
    char medications[500];
	ifstream fin;
	fin.open("./files/J)Disease-Med.txt");
	if(fin.is_open())
	{
		while(!fin.eof())
		{
			fin.getline(disease,500,'-');
			fin.getline(medications, 500, '!');
			fin.getline(extra, 5000, '\n');
			root = insert(root, disease, medications);
		}
	}
	else
	{
		cout<<"\nFile couldn't be opened\n";
		return NULL;
	}
	fin.close();
	return root;
}

Node* AVL::insert(Node *r, string d, char* med)
{
    if(r == NULL)
	{
        r = new Node(d, med);
        return r;
    }

    if(d < r->disease)
    {
        r->left = insert(r->left, d, med);
    }

    else if(d > r->disease)
	{
        r->right = insert(r->right, d, med);
    }

    else
	{
        cout << "Duplicates not allowed" << endl;
        return r;
    }

    int bf = getBalanceFactor(r);

    if(bf > 1 && d < r->left->disease)
	{
        return rightRotate(r);
    }

    if(bf < -1 && d > r->right->disease)
	{
        return leftRotate(r);
    }

    if(bf > 1 && d > r->left->disease)
	{
        r->left = leftRotate(r->left);
        return rightRotate(r);
    }

    if(bf < -1 && d < r->right->disease)
	{
        r->right = rightRotate(r->right);
        return leftRotate(r);
    }

    return r;
}

Node* AVL::search(Node* root, string val_to_find)
{
    if(root == NULL)
    {
    	TextColor(4);
    	cout << " No medications\n" << endl ;
      	return NULL;
    }

    if(root->disease == val_to_find)
    {
    	TextColor(1);
    	cout << "\nThe medications of ' ";
    	TextColor(4);
		cout << val_to_find;
		TextColor(1);
		cout << " ' are:" << endl ;
      	return root; 
    }
    else
    {
        if(val_to_find > root->disease)
        {
        	return search(root->right, val_to_find) ;
        }
      
      	else if(val_to_find < root->disease)
        {
        	return search(root->left, val_to_find) ;
        }
      
    }
    
}


//BST class functions

BSTNode* BST::insertFromFile(BSTNode *r)
{
    char disease[500];
    char extra[5000];
	char e;
    char symptoms[500];
	ifstream fin;
	fin.open("./files/L)Disease-Sym.txt");
	if(fin.is_open())
	{
		while(!fin.eof()){
			fin.getline(disease,500,'-');
			fin.getline(symptoms, 500, '!');
			fin.getline(extra, 5000, '\n');
			root = insert(root, disease, symptoms);
		}
	}
	else
	{
		cout<<"\nFile couldn't be opened\n";
		return NULL;
	}
	
	fin.close();
	return root;
}

BSTNode* BST::insert(BSTNode *r, string d, char* med)
{
    if (r == NULL)
    {
    	r = new BSTNode(d, med);
        return r;
    }
	if(d < r->disease)
	{
	    r->left= insert(r->left, d, med);
    }
	if(d > root->disease)
	{
        r->right= insert(r->right, d, med);
    }
    
    return r;
}

BSTNode* BST::BSTNodeSearch(BSTNode* root, string find)
{
    if (root == NULL)
    {
	    TextColor(4);
	    cout<<"\n\n\n\n\nHERfgfgfdgdfg";
        cout << " No symptoms\n" << endl ;
        return NULL;
    }
    
    if (root->disease == find)
    {
    	TextColor(1);
    	cout << "\nThe symptoms of ' ";
    	TextColor(4);
		cout << find;
		TextColor(1);
		cout << " ' are:" << endl ;
        return root;
    }
    else if(root->disease > find)
	{
 	    return BSTNodeSearch(root->left, find);
    }
    
    return BSTNodeSearch(root->right, find);
}



//search for the medications of the recongnized diseases

void medicationsForDiagnosedDisease(string finalDisease)
{
	Node* root = NULL;
    AVL tree;
    tree.root = tree.insertFromFile(tree.root);
	
	Node* n = tree.search(tree.root, finalDisease);
	TextColor(2);
    int i = 0;
    
    if(n!=NULL)
	{
    	while(n->medications[i])
		{	
    		if(n->medications[i] == '-')
			{
		        cout << endl;
		    }
		    else
			{
	 	        cout << n->medications[i];	
			}
			
			i++;
	    }
    }
}

//search for the symptoms of the disease

void symptomsForDiagnosedDisease(string finalDisease)
{
	BSTNode* root = NULL;
    BST tree;
    tree.root = tree.insertFromFile(tree.root);
    cout << tree.root->disease;
	
	BSTNode* n = tree.BSTNodeSearch(tree.root, finalDisease);
	TextColor(2);
    int i = 0;
    
    if(n!=NULL)
	{
    	while(n->symptoms[i])
		{	
    		if(n->symptoms[i] == '-')
			{
		        cout << endl;
		    }
		    else
			{
	 	        cout << n->symptoms[i];	
			}
			
			i++;
	    }
    }
}


//Prediction System

void predict()
{
	FontSize(0,20); //ui
	g1.clear();
	g1.push_back(v1);
	g.BFS(v1);
	g1.clear();
	cout << endl;
	while(1)
	{
		int a;
        TextColor(1);
	    cout << "\nEnter Body Parts you are having symptoms or  -1  to stop entering: " ;
	    TextColor(2);
	    a = inputValidationForBodyParts(); //takes values between 11001-11053 or -1 
        if(a == -1)
        {
		    break;
	    }
	    g1.push_back(a);
	}
	
	TextColor(15);
	for(int i = 0 ; i < g1.size() ; i++)
	{
	    if(i==0)
		{
			TextColor(1);
		    cout << "\n\nThe body parts you selected are: ";
		    TextColor(15);
		}
		g.BFS(g1[i]);

	}
	
	g1.clear();
	cout << endl;
	while(1)
	{
		int a;
		TextColor(1);
		cout << "\nEnter the symptoms you are having or  -1  to stop entering: " ;
		TextColor(2);
		a = inputValidationForSymptoms();
		if(a == -1)
		{
			break;
		}
		g1.push_back(a);
	}
	
	TextColor(15);
	for(int i = 0 ; i < g1.size() ; i++)
	{
	    if(i==0)
		{
			TextColor(1);
		    cout << "\n\nThe symptom  you selected are: ";
		    TextColor(15);
		}
		g.BFS(g1[i]);
	}
	
	int max = 0;
	int finalDiseaseID;
	string finalDisease;
	
	for(int i = 0 ; i < diseaseCountVec.size(); i++)
	{
		if(diseaseCountVec[i].second > max){
			max = diseaseCountVec[i].second;
			finalDiseaseID = diseaseCountVec[i].first;
		}
	}
	
	for(int i = 0 ; i < diseasesVec.size(); i++)
	{
		if(finalDiseaseID == diseasesVec[i].first){
			finalDisease = diseasesVec[i].second;
			break;
		}
	}
	
	TextColor(15);
	cout << "\n\n\t\t\t\t\t\tThe disease is: ' ";
	TextColor(4);
	cout << finalDisease;
	TextColor(15);
	cout << " '\n\n" << endl;

	medicationsForDiagnosedDisease(finalDisease);
	
	//ui
	TextColor(1);
	cout << "\n\nPress any key to move to main menu";
	getch();
	system("cls");
	loadingAnimation();
	system("color 0F");
}

void medicineLookup()
{
	int DiseaseID;
	string disease;
	while(1)
	{
		system("cls");
		TextColor(15);
		for(int i = 0 ; i < diseasesVec.size(); i++)
		{
		    cout << diseasesVec[i].first << "  " << diseasesVec[i].second << endl;
		}	
		TextColor(1);
		cout << "\nEnter the disease whose medications you want to search or   a   to go back: ";
		TextColor(2);
		DiseaseID = inputValidationForDiseases();
		
		for(int i = 0 ; i < diseasesVec.size(); i++)
		{
			if(DiseaseID == diseasesVec[i].first){
				disease = diseasesVec[i].second;
				break;
			}
		}
		
		
		if(DiseaseID == 0)
		{
			break;
		}
		else
		{
			medicationsForDiagnosedDisease(disease);
			TextColor(1);
			cout << "\nEnter any key to continue: ";
			getch();
		}
	}
	
	//ui
	TextColor(1);
	cout << "\n\nPress any key to move to main menu";
	getch();
	system("cls");
	loadingAnimation();
	system("color 0F");
	
}

void symptomLookup()
{
	int DiseaseID;
	string disease;
	while(1)
	{
	    system("cls");
		TextColor(15);
		for(int i = 0 ; i < diseasesVec.size(); i++)
		{
			cout << diseasesVec[i].first << "  " << diseasesVec[i].second << endl;
		}
		
		TextColor(1);
		cout << "\nEnter the disease whose symptoms you want to search or   a   to exit: ";
		TextColor(2);
		DiseaseID = inputValidationForDiseases();
		
		int i;
		for( i = 0 ; i < diseasesVec.size(); i++)
		{
			if(DiseaseID == diseasesVec[i].first){
				break;
			}
		}
		
		stringstream s;
		s << diseasesVec[i].first;
		s >> disease;
		TextColor(1);
	    if(DiseaseID == 0)
		{
			break;
		}
		else
		{
			symptomsForDiagnosedDisease(disease);
			TextColor(1);
			cout << "\nEnter any key to continue: ";
			getch();
		}
	}
	
	//ui
	TextColor(1);
	cout << "\n\nPress any key to move to main menu";
	getch();
	system("cls");
	loadingAnimation();
	system("color 0F");
	
}

void sort(vector <pair <int, string> > & diseasesVec)
{
	
    if (diseasesVec.size() <= 1) return;

    int mid = diseasesVec.size() / 2;
    vector<pair <int, string> > left;
    vector<pair <int, string> > right;

    for (size_t j = 0; j < mid;j++)
        left.push_back(diseasesVec[j]);
    for (size_t j = 0; j < (diseasesVec.size()) - mid; j++)
        right.push_back(diseasesVec[mid + j]);

    sort(left);
    sort(right);
    mergeSort(left, right, diseasesVec);
}

void mergeSort(vector <pair <int, string> > &left, vector <pair <int, string> > &right, vector <pair <int, string> > &diseasesVec)
{
    int nL = left.size();
    int nR = right.size();
    int i = 0, j = 0, k = 0;

    while (j < nL && k < nR) 
    {
        if (left[j].first < right[k].first)
		{
            diseasesVec[i] = left[j];
            j++;
        }
        else
		{
            diseasesVec[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL)
	{
        diseasesVec[i] = left[j];
        j++; i++;
    }
    while (k < nR)
	{
        diseasesVec[i] = right[k];
        k++; i++;
    }
}

void sortForDiseasesVec()
{
    sort(diseasesVec);
}

void sortForbodyPartsVec()
{
    sort(bodyPartsVec);
}

void sortForsymptomsVec()
{
    sort(symptomsVec);
}

void diseaseDescription()
{
	char extra[5000];
	char e;
	char D[5000];
	char description[5000];
	int DiseaseID;
	string disease;
	int count1, count2;
	while(1)
	{
		system("cls");
		TextColor(15);
	    for(int i = 0 ; i < diseasesVec.size(); i++)
		{
			cout << diseasesVec[i].first << "  " << diseasesVec[i].second << endl;
		}
		
		TextColor(1);
		cout << "\nEnter the disease whose symptoms you want to search: ";
		TextColor(2);
		DiseaseID = inputValidationForDiseases();
		
		for(int i = 0 ; i < diseasesVec.size(); i++)
		{
			if(DiseaseID == diseasesVec[i].first){
				disease = diseasesVec[i].second;
				break;
			}
		}
		
		if(DiseaseID == 0)
		{
			break;
		}
		else
		{
	        count1 = count2 = 0;
			ifstream fin;
			fin.open("./files/Z)DiseaseDescription.txt");
			while(!fin.eof())
			{
				fin.getline(extra, 5000, '-');
				fin.getline(D, 5000, '-');
				
				for(int i = 0; disease[i] != '\0'; i++)
				{
					count1++;
					if(disease[i] == D[i])
					    count2++;
				}
				
				if(count1 == count2 && count2!=0 && count2 !=0)
				{
					fin.getline(description, 5000, '\n');
					break;
				}
				count1 = count2 = 0;
				fin.getline(extra, 5000, '\n');
				
			}
			fin.close();
			
			TextColor(1);
			cout << "\nThe description of the disease '";
			TextColor(4);
			cout << disease;
			TextColor(1);
			cout << " 'is\n";
			TextColor(15);
			cout << description;
			
			TextColor(1);
			cout << "\n\nEnter any key to continue: ";
			getch();
		}

	}

	//ui
	TextColor(1);
	cout << "\n\nPress any key to move to main menu";
	getch();
	system("cls");
	loadingAnimation();
	system("color 0F");
}
