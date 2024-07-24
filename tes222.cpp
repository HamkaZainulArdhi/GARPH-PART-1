#include <iostream>
using namespace std;
struct myTree{
 myTree* right;
 char myData;
 myTree* left;
};
myTree* theNode;
myTree* root;
myTree* now;
myTree* helperA;
myTree* helperB;
myTree* nodeAddress[256];
void init(){
 root = NULL;
}
void newNode(char inputData){
 theNode = new myTree;
 theNode->myData = inputData;
 theNode->right = NULL;
 theNode->left = NULL;
}
void rootNode(){
 if(root == NULL){
 char yourData;
 cout<<"Enter the data : ";
 cin>>yourData;
 newNode(yourData);
 root = theNode;
 cout<<"Root created..."<<endl;
 }else{
 cout<<"Root already exists..."<<endl;
 }
}
void addingNode(){
 if(root != NULL){
 int i, j, theMark;
 char dataUser;
 i = 1; j = 1; theMark = 0;
 nodeAddress[i] = root;
 while(theMark == 0 && j < 256){
 cout<<"Enter the left data : ";
 cin>>dataUser;
 if(dataUser != '0'){
 newNode(dataUser);
 now = nodeAddress[i];
 now->left = theNode;
 j++;
 nodeAddress[j] = theNode;
 }else{
 theMark = 1;
 j++;
 nodeAddress[j] = NULL;
 }
 if(theMark == 0){
 cout<<"Enter the right data : ";
 cin>>dataUser;
 if(dataUser != '0'){
 newNode(dataUser);
 now = nodeAddress[i];
 now->right = theNode;
 j++;
 nodeAddress[j] = theNode;
 }else{
 theMark = 1;
 j++;
 nodeAddress[j] = NULL;
 }
 }
 i++;
 }
 }
}
void theXFunction(myTree *theNode){
 if(theNode != NULL){
 cout<<theNode->myData<<" ";
 theXFunction(theNode->left);
 theXFunction(theNode->right);
 }
}
void theZFunction(myTree *theNode){
 if(theNode != NULL){
 theXFunction(theNode->left);
 theXFunction(theNode->right);
 cout<<theNode->myData<<" ";
 }
}

void theYFunction(myTree *theNode){
 if(theNode != NULL){
 theXFunction(theNode->left);
 cout<<theNode->myData<<" ";
 theXFunction(theNode->right);
 }
}
int main()
{
 rootNode();
 addingNode();

 return 0;
}