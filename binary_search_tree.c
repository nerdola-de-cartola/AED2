/*
 * 
 * =============================================================================
 * Aplicação modelo para implementação de Árvores Binárias de Busca (ABB)
 * =============================================================================
 * 
 * Autor: Wanderley de Souza Alencar 
 * 
 * Obs..: Aplicação desenvolvida para fins didáticos (exclusivamente).
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h> 


#define INVALID_KEY    -1
#define INVALID_HEIGTH -1
#define FALSE           0
#define TRUE            1
#define ESPACAMENTO     5

//
//------------------------------------------------------------------------------ 
// Declaração da estrutura do "nó" e da árvore, bem como os ponteiros
// correspondentes
//------------------------------------------------------------------------------ 
//

typedef struct TTreeNode * PTreeNode;

typedef struct TTreeNode {
    PTreeNode lChild;
    unsigned int key;
    unsigned int data;
    PTreeNode rChild;
} TTreeNode;

//
//------------------------------------------------------------------------------
// Protótipos das funções
//------------------------------------------------------------------------------
//

PTreeNode BTreeNodeCreate(unsigned int key, unsigned int data);
void      BTreeCreate(PTreeNode * bTreeRoot);
void      BTreeInsert(PTreeNode * bTreeRoot, TTreeNode node);
void      BTreeInsert_Iterative(PTreeNode * bTreeRoot, TTreeNode node);
PTreeNode BTreeBiggestNodeOnRigth(PTreeNode *bTreeRoot);
PTreeNode BTreeSmallestNodeOnLeft(PTreeNode *bTreeRoot); 
void       BTreeRemoveNode(PTreeNode * bTreeRoot, TTreeNode node);
PTreeNode BTreeSearch(PTreeNode bTreeRoot, unsigned int key);
void      BTreePrefixTraversal(PTreeNode bTreeRoot);
void      BTreeInfixTraversal(PTreeNode bTreeRoot);
void      BTreePostfixTraversal(PTreeNode bTreeRoot);
int       BTreeHeigth(PTreeNode bTreeRoot);
int       BTreeSize(PTreeNode bTreeRoot);
void      BTreeDestroy(PTreeNode * bTreeRoot);
void      BTreePrint2D(PTreeNode bTreeRoot, int localSpace);
void      BTreeProcessLevel(PTreeNode bTreeRoot, int level);
void      BTreeBFS(PTreeNode bTreeRoot);

//
//------------------------------------------------------------------------------
// Implementação das funções...
//------------------------------------------------------------------------------
//

PTreeNode BTreeNodeCreate(unsigned int key, unsigned int data) {
    
    PTreeNode newNode;
    
    newNode = (PTreeNode) malloc(sizeof(struct TTreeNode));
    
    newNode->lChild = (PTreeNode) NULL;
    newNode->key    = key;
    newNode->data   = data;   
    newNode->rChild = (PTreeNode) NULL;
    return(newNode); 
    
}

void BTreeCreate(PTreeNode * bTreeRoot) {
    
    (*bTreeRoot) = (PTreeNode) NULL;
}

void BTreeInsert(PTreeNode * bTreeRoot, TTreeNode node) {
   
   if ((*bTreeRoot) != NULL) {
       if (node.key < (*bTreeRoot)->key ) {
           BTreeInsert(&((*bTreeRoot)->lChild), node);
       }
       else {
           if (node.key > (*bTreeRoot)->key) {
               BTreeInsert(&((*bTreeRoot)->rChild), node);
           }
           else {
               //
               // Não deveria haver chaves coincidentes --> chave primária violada
               // [Não insere a última fornecida]
               //
           }
       }
   } 
   else {
       (*bTreeRoot) = BTreeNodeCreate(node.key, node.data);
   }     
}

void BTreeInsert_Interactive(PTreeNode * bTreeRoot, TTreeNode node) {
   
   PTreeNode newNode, pAuxiliary; 
   
   newNode    = BTreeNodeCreate(node.key, node.data);
   pAuxiliary = bTreeRoot;
   while (pAuxiliary != NULL) do {
      if (newNode->key < pAuxiliary->key) {
         if (pAuxiliary->lChild == NULL) {
            pAuxiliary-> = newNode;
            return();
         }
         else {
            pAuxiliary = pAuxiliary->lChild;
         } 
      }
      else {
         if (newNode->key > pAuxiliary->key) {
            if (pAuxiliary->rChild == NULL) {
               pAuxiliary->rChild = newNode;
               return();
            }
            else {
               pAuxiliary = pAuxiliary->rChild;
           }  
         else {
           //
           // Não deveria haver chaves coincidentes --> chave primária violada.
           //
         }     
      }
   }  
   (bTreeRoot) = newNode;
}


void BTreeInsert_Iterative(PTreeNode * bTreeRoot, TTreeNode node) {
   PTreeNode pAuxiliar;
   
   pAuxiliar = (*bTreeRoot);
   while (pAuxiliar != NULL) {
       if (node.key < pAuxiliar->key ) {
           bTreeRoot = &(pAuxiliar->lChild);
       }
       else {
           bTreeRoot = &(pAuxiliar->rChild);
       }
   } 
   pAuxiliar    = BTreeNodeCreate(node.key, node.data);
   (*bTreeRoot) = pAuxiliar;
}

PTreeNode BTreeBiggestNodeOnRigth(PTreeNode *bTreeRoot) {
    
    PTreeNode pAuxiliar; 
    
    if ((*bTreeRoot)->rChild != NULL) {
        return(BTreeBiggestNodeOnRigth(&(*bTreeRoot)->rChild));
    }
    else {
      pAuxiliar = (*bTreeRoot);
      if ((*bTreeRoot)->lChild != NULL) {
          //
          // Preservando os filhos "à esquerda" do nó...
          //
          (*bTreeRoot) = (*bTreeRoot)->lChild;
      }
      else {
          (*bTreeRoot) = (PTreeNode) NULL;
      }
      return(pAuxiliar);
    }
    
}

PTreeNode BTreeSmallestNodeOnLeft(PTreeNode *bTreeRoot) {
    
    PTreeNode pAuxiliar; 
    
    if ((*bTreeRoot)->lChild != NULL) {
        return(BTreeSmallestNodeOnLeft(&(*bTreeRoot)->lChild));
    }
    else {
      pAuxiliar = (*bTreeRoot);
      if ((*bTreeRoot)->rChild != NULL) {
          //
          // Preservando os filhos "à direita" do nó...
          //
          (*bTreeRoot) = (*bTreeRoot)->rChild;
      }
      else {
          (*bTreeRoot) = (PTreeNode) NULL;
      }
      return(pAuxiliar);
    }
    
}


void BTreeRemoveNode(PTreeNode * bTreeRoot, TTreeNode node) {
   
   PTreeNode pAuxiliar; 
   
   if ((*bTreeRoot) != NULL) {
       if (node.key < (*bTreeRoot)->key ) {
           BTreeRemoveNode(&((*bTreeRoot)->lChild), node);
       }
       else {
           if (node.key > (*bTreeRoot)->key) {
               BTreeRemoveNode(&((*bTreeRoot)->rChild), node);
           }
           else {
               //
               // Chave a ser removida encontrada...
               //
               pAuxiliar = (*bTreeRoot);
               if ( ((*bTreeRoot)->lChild == NULL) && ((*bTreeRoot)->rChild == NULL) ) {
                   //
                   // Removendo um nó que não possui filhos...
                   //
                   free(pAuxiliar);
                   (*bTreeRoot) = NULL;
               }
               else { 
                   if ((*bTreeRoot)->lChild == NULL) {
                      //
                      // Removendo um nó que só possui filho "à direita"
                      //
                      (*bTreeRoot) = (*bTreeRoot)->rChild;
                      pAuxiliar->rChild = (PTreeNode) NULL;
                      free(pAuxiliar);
                      pAuxiliar = (PTreeNode) NULL;
                   }
                   else {
                      if ((*bTreeRoot)->rChild == NULL) {
                         //
                         // Removendo um nó que só possui filho "à esquerda"
                         //
                         (*bTreeRoot) = (*bTreeRoot)->lChild;
                         pAuxiliar->lChild = (PTreeNode) NULL;
                         free(pAuxiliar);
                         pAuxiliar = (PTreeNode) NULL;                          
                      }  
                      else {
                          //
                          // O nó a ser removido tem os dois filhos (esquerda, direita) e, por isso,
                          // escolhe-se fazer o "maior filho" direito da subárvore à esquerda
                          //
                          pAuxiliar = BTreeBiggestNodeOnRigth(&(*bTreeRoot)->lChild);
                          pAuxiliar->lChild    = (*bTreeRoot)->lChild;
                          pAuxiliar->rChild    = (*bTreeRoot)->rChild;
                          
                          (*bTreeRoot)->lChild = (PTreeNode) NULL;
                          (*bTreeRoot)->rChild = (PTreeNode) NULL;
                          
                          free((*bTreeRoot));
                          (*bTreeRoot) = pAuxiliar;
                          pAuxiliar    = (PTreeNode) NULL;
                      }
                   }
               }
               
           }
       }
   };
}
//
// 
//
//
PTreeNode BTreeSearch(PTreeNode bTreeRoot, unsigned int key) {
   
   if (bTreeRoot == NULL) {
      return(NULL); 
   } 
   else {
      if (bTreeRoot->key == key) {
         return(bTreeRoot);
      }  
      else {
          if (bTreeRoot->key < key) {
            //
            // Pesquisa na subárvore à direita do nó atual...  
            //
             return(BTreeSearch(bTreeRoot->rChild, key));   
          }
          else {
            //
            // Pesquisa na subárvore à esquerda do nó atual...  
            //  
             return(BTreeSearch(bTreeRoot->lChild, key));   
          }
      }
   }     
}

void BTreePrefixTraversal(PTreeNode bTreeRoot) {
    if (bTreeRoot != NULL) {
        printf("[(key, data) = (%u %u)]\n", bTreeRoot->key, bTreeRoot->data);        
        BTreePrefixTraversal(bTreeRoot->lChild);
        BTreePrefixTraversal(bTreeRoot->rChild);
    };  
}

void BTreeInfixTraversal(PTreeNode bTreeRoot) {
    if (bTreeRoot != NULL) {
        BTreeInfixTraversal(bTreeRoot->lChild);
        printf("[(key, data) = (%u %u)]\n", bTreeRoot->key, bTreeRoot->data);
        BTreeInfixTraversal(bTreeRoot->rChild);
    };      
}

void BTreePostfixTraversal(PTreeNode bTreeRoot) {
    if (bTreeRoot != NULL) {
        BTreePostfixTraversal(bTreeRoot->lChild);
        BTreePostfixTraversal(bTreeRoot->rChild);
        printf("[(key, data) = (%u %u)]\n", bTreeRoot->key, bTreeRoot->data);                
    };  
}

int BTreeHeigth(PTreeNode bTreeRoot) {
    int leftHeigth, rightHeigth; 
    
    if (bTreeRoot != NULL) {
        leftHeigth  = BTreeHeigth(bTreeRoot->lChild);
        rightHeigth = BTreeHeigth(bTreeRoot->rChild);
        return(leftHeigth>rightHeigth?(leftHeigth+1):(rightHeigth+1));
    }
    else {
        return(INVALID_HEIGTH);
    }
}

int BTreeSize(PTreeNode bTreeRoot) {
    int leftHeigth, rightHeigth; 
    
    if (bTreeRoot != NULL) {
        return(1 + BTreeSize(bTreeRoot->lChild) + BTreeSize(bTreeRoot->rChild));
    }

    else {
        return(0);
    }
}

void BTreeDestroy(PTreeNode * bTreeRoot) {
    if ((*bTreeRoot) != NULL) {
        BTreeDestroy(&(*bTreeRoot)->lChild);
        BTreeDestroy(&(*bTreeRoot)->rChild);
        free((*bTreeRoot));
    }
}


void BTreePrint2D(PTreeNode bTreeRoot, int localSpace) {
    int i;
    
    if (bTreeRoot != NULL) {
       localSpace += ESPACAMENTO;
       BTreePrint2D(bTreeRoot->rChild, localSpace);
       printf("\n");
       for (i = ESPACAMENTO; (i < localSpace); i++)
           printf(" ");
       printf("%u\n",bTreeRoot->data);
       BTreePrint2D(bTreeRoot->lChild, localSpace);
    };
}

void BTreeProcessLevel(PTreeNode bTreeRoot, int level) {
    if (bTreeRoot != NULL) {
       if (level = 0) {
           printf("[%u, %u]", bTreeRoot->key, bTreeRoot->data);
       } 
       else {
           if (level > 0) {
               BTreeProcessLevel(bTreeRoot->lChild, level - 1);
               BTreeProcessLevel(bTreeRoot->rChild, level - 1);
           }
       }
    }
}

void BTreeBFS(PTreeNode bTreeRoot) {
    int level, bTHeight;
    
    bTHeight = BTreeHeigth(bTreeRoot);
    for (level = 0; (level < bTHeight); level++) {
        BTreeProcessLevel(bTreeRoot, level);
    }
}

/*
 * 
 */
int main(int argc, char** argv) {

    unsigned int operation,
                 initialized;
    TTreeNode    userNode;  
    PTreeNode    binarySearchTree,
                 pAuxiliar;
    

    operation   = 0;
    initialized = FALSE;
    do {
        printf("\n\nÁrvore Binária de Busca - ABB\n\n");
        printf("[ 1] - Criar\n");
        printf("[ 2] - Inserir chave/dado\n");
        printf("[ 3] - Remover chave/dado\n");        
        printf("[ 4] - Pesquisar chave\n");
        printf("[ 5] - Percurso Pré-fixado\n");
        printf("[ 6] - Percurso Central\n");
        printf("[ 7] - Percurso Pós-fixado\n");
        printf("[ 8] - Calcular tamanho\n");
        printf("[ 9] - Calcular altura\n");
        printf("[10] - Imprimir graficamente (2D)\n");
        printf("[ 0] - Sair\n");        
        printf("Operação: ");
        scanf("%u", &operation);
        switch (operation) {
            case 0 : 
              {
                  printf("\nFinalizando a execução da aplicação.\n");
                  break;
              }
            case 1 : 
              {   
                if (initialized) {
                    printf("\nUma árvore já havia sido inicializada anteriormente.");
                    printf("\nDeseja destruí-la e recriar uma nova árvore?");
                    printf("\n[1] Sim, destruir e recriar   [2] Cancelar a operação");
                    printf("\nOperação: ");
                    do {
                        scanf("%u", &operation);
                    } while ((operation != 1) && (operation != 2));
                    if (operation == 1) {
                        //
                        // Executar rotina para destruir completamente a árvore...
                        //
                        BTreeDestroy(&binarySearchTree);
                    }
                }
                else {
                  BTreeCreate(&binarySearchTree);
                  initialized = TRUE;  
                  printf("\nÁrvore binária de busca criada.");
                  printf("\nNo momento ela está VAZIA.");                
                };                  
                break;
              }
            case 2 : 
              {
                if (initialized) {
                    do {
                        printf("\nForneça o valor da chave a ser INSERIDA ou [0] para finalizar: ");
                        scanf("%u", &userNode.key);
                        if (userNode.key != 0) {
                            printf("Forneça o valor do dado para a chave [%u]: ", userNode.key);
                            scanf("%u", &userNode.data);
                            BTreeInsert(&binarySearchTree, userNode); 
                            
                        }
                    } while (userNode.key != 0);                    
                }  
                break;      
              }
            case 3 : 
              {
                if (initialized) {
                    do {
                        printf("\nForneça o valor da chave a ser REMOVIDA ou [0] para finalizar: ");
                        scanf("%u", &userNode.key);
                        if (userNode.key != 0) {
                            BTreeRemoveNode(&(binarySearchTree), userNode);
                            printf("Chave removida.\n"); 
                        }
                        
                    } while (userNode.key != 0);
                }  
                break;             
              }          
            case 4 : 
              {
                if (initialized) {
                    do {
                        printf("\nForneça o valor da chave a ser PESQUISADA ou [0] para finalizar: ");
                        scanf("%u", &userNode.key);
                        if (userNode.key != 0) {
                            pAuxiliar = BTreeSearch(binarySearchTree, userNode.key);
                            if (pAuxiliar != NULL) {
                               printf("O dado associado à chave [%u] é [%u].\n", pAuxiliar->key, pAuxiliar->data); 
                            }
                            else {
                               printf("A chave [%u] não está na árvore.\n", userNode.key); 
                            }
                        }
                    } while (userNode.key != 0);
                    
                }  
                break;             
              }
            case 5 : {
                if (initialized) {
                    printf("\nPercurso PRÉ-FIXADO na árvore.\n");
                    BTreePrefixTraversal(binarySearchTree);
                    
                }
                break;
            }
            
            case 6 : {
                if (initialized) {
                    printf("\nPercurso CENTRAL na árvore.\n");
                    BTreeInfixTraversal(binarySearchTree);
                    
                }
                break;
            }
            case 7 : {
                if (initialized) {
                    printf("\nPercurso PÓS-FIXADO na árvore.\n");
                    BTreePostfixTraversal(binarySearchTree);
                }
                break;
            }
            case 8 : {
                if (initialized) {
                    printf("\nA árvore possui tamanho igual a [%d].\n", BTreeSize(binarySearchTree));
                }
                break;
            }                        
            case 9 : {
                if (initialized) {
                    printf("\nA árvore possui altura igual a [%d].\n", BTreeHeigth(binarySearchTree));
                }
                break;
            } 
            case 10 : {
                if (initialized) {
                    BTreePrint2D(binarySearchTree, 2);
                }
                break;
            } 
        } 
                
    }
    while (operation != 0);
    
    
    return (EXIT_SUCCESS);
}

