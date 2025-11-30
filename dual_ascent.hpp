#include<vector> 
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <math.h>  
#include <algorithm>

   class dual_ascent{



    float * x;
    float * b;
    float **A;
    float *Z;
    float zobj; 
    int number_objectives; 
    int number_constraints;
    int number_variables;
    



   
    public: 


      Simplexe(std::string name) 
      {

   
            std::ifstream fichier(name);
                if(fichier){
                    
                    fichier >> number_objectives; 
                    std::cout << number_objectives << std::endl; 
                    fichier >> number_variables;
                    std::cout << number_variables << std::endl; 

                    fichier >> number_constraints;
                    dict_form = new Dictionnary(number_variables,number_constraints);
                     zobj = 0;
                     x = new float[number_variables];
                     b = new float[number_constraints]; 
                     Z  = new float[number_variables];
                    A = new float*[number_constraints];
                    for(int i = 0; i < number_constraints; i++){
                        A[i] = new float[number_variables + 1]; 
                    }
                    for(int i = 0; i < number_variables; i++){
                     fichier >> Z[i];
                    }

                    for(int i = 0; i < number_constraints; i++){
                        for(int j = 0; j < number_variables; j++){
                            fichier >> A[i][j];

                        }
                    }
                    
                    
                    for(int i = 0; i < number_constraints; i++){
                        fichier >> b[i];
                    }
                }


                



            }

        void display_simplex(){
            std::cout << "Number of constraints: " << number_constraints << std::endl; 
            std::cout << "Number of Variables: " << number_variables << std::endl;

            std::cout << "Objective function: ";
            for(int i = 0; i < number_variables; i++){
                std::cout << Z[i] << " ";
            }
            std::cout << std::endl; 
            std::cout << "Constraint bounds: ";

            for (int i = 0 ; i < number_constraints; i++){
                std::cout << b[i] << " ";
            }
            std::cout << std::endl;
            std::cout << "Matrix constraints: ";

               for(int i = 0; i < number_constraints; i++){
                        for(int j = 0; j < number_variables; j++){
                              std::cout << A[i][j] << " ";

                        }
                         std::cout << std::endl; 
                    }

        }


        void fill_dictionnary(){
                 for(int i = 0; i < number_constraints; i++){
                    for(int j = 0; j < number_variables; j++){
                            dict_form->constraint_matrix[i][j] =  A[i][j];

                        }

                    }
                    for(int i = 0; i < number_constraints; i++){
                        for (int j = number_variables; j < number_variables + number_constraints; j++){
                            dict_form->constraint_matrix[i][j] =  0;

                        }

                        dict_form->constraint_matrix[i][number_variables + i] = 1; 

                    }
                    for(int i = 0; i < number_variables; i++){
                        dict_form->Cj_Zj[i] = Z[i];
                    }
                    for(int i = 0; i < number_constraints; i++){
                        dict_form->Cj_Zj[number_variables + i] = 0 ; 
                        dict_form->constraint_matrix[i][number_constraints + number_variables] = b[i];

                    }
                    dict_form->Cj_Zj[number_variables + number_constraints] = 0; 


            
        }


        
        void display_dictionnary(){
            std::cout << "Number of constraints: " << number_constraints << std::endl; 
            std::cout << "Number of Variables: " << number_variables << std::endl;
            std::cout << "Cj_Zj: ";
            for(int i = 0; i < number_variables + number_constraints + 1; i++){
                std::cout << dict_form->Cj_Zj[i] << " ";
            }
            std::cout << std::endl; 
            std::cout << "Matrix constraints dictionnary: ";
            for(int i = 0; i < number_constraints; i++){
                for(int j = 0; j < number_variables + number_constraints + 1; j++){
                    std::cout << dict_form->constraint_matrix[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }


        void resolve_simplexe(){
            fill_dictionnary();
            int iteration_number = 0;
            bool stop = false; 
            std::cout << "nbvar: " << number_variables << std::endl;  
            while (stop == false){
                std::cout << "iteration number is: " << iteration_number << std::endl; 
                for(int i = 0; i < number_variables; i ++){
                    std::cout << "Ciji: " << dict_form->Cj_Zj[i] << std::endl;
                    if(dict_form->Cj_Zj[i] > 0){
                        iteration_number += 1;
                        std::cout << "iteration number is: " << iteration_number << std::endl; 
                        dict_form->choose_input_index();
                        dict_form->choose_pivot_line();
                        dict_form->pivot_dictionnary(); 
                        display_dictionnary();

                        if(iteration_number >= number_variables){
                        stop = true;
                        std::cout << "Stop condition reached, exiting loop." << std::endl;
                        break;
                    }


                    }
            

                }
                


            }

        }

};