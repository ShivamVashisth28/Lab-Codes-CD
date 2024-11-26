#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RULES 100
#define MAX_LENGTH 100

// Struct for storing non-terminal details
typedef struct {
    char name[MAX_LENGTH];            // Name of the non-terminal (head of the production rule)
    char productionRules[MAX_RULES][MAX_LENGTH];  // Production rules for the non-terminal
    int ruleCount;                    // Number of production rules
} NonTerminal;

// Struct for storing the grammar
typedef struct {
    NonTerminal nonTerminals[MAX_RULES];
    int nonTerminalCount;
} Grammar;

// Function to initialize a non-terminal
void initNonTerminal(NonTerminal* nt, const char* name) {
    strcpy(nt->name, name);
    nt->ruleCount = 0;
}

// Function to add a production rule to a non-terminal
void addRule(NonTerminal* nt, const char* rule) {
    if (nt->ruleCount < MAX_RULES) {
        strcpy(nt->productionRules[nt->ruleCount], rule);
        nt->ruleCount++;
    }
}

// Function to print the production rules of a non-terminal
void printRule(NonTerminal* nt) {
    printf("%s ->", nt->name);
    for (int i = 0; i < nt->ruleCount; i++) {
        printf(" %s |", nt->productionRules[i]);
    }
    printf("\b \n");
}

// Function to initialize a grammar
void initGrammar(Grammar* grammar) {
    grammar->nonTerminalCount = 0;
}

// Function to add a production rule to the grammar
void addGrammarRule(Grammar* grammar, const char* rule) {
    int nt = 0;
    char parse[MAX_LENGTH];
    int parseIndex = 0;

    for (int i = 0; rule[i] != '\0'; i++) {
        if (rule[i] == ' ') {
            if (!nt) {
                NonTerminal newNonTerminal;
                parse[parseIndex] = '\0';
                initNonTerminal(&newNonTerminal, parse);
                grammar->nonTerminals[grammar->nonTerminalCount++] = newNonTerminal;
                nt = 1;
                parseIndex = 0;
            } else {
                parse[parseIndex] = '\0';
                addRule(&grammar->nonTerminals[grammar->nonTerminalCount - 1], parse);
                parseIndex = 0;
            }
        } else if (rule[i] != '|' && rule[i] != '-' && rule[i] != '>') {
            parse[parseIndex++] = rule[i];
        }
    }
    if (parseIndex > 0) {
        parse[parseIndex] = '\0';
        addRule(&grammar->nonTerminals[grammar->nonTerminalCount - 1], parse);
    }
}

// Function to solve non-immediate left recursion
void solveNonImmediateLR(Grammar* grammar, NonTerminal* A, NonTerminal* B) {
    char newRulesA[MAX_RULES][MAX_LENGTH];
    int newRuleCount = 0;

    for (int i = 0; i < A->ruleCount; i++) {
        if (strncmp(A->productionRules[i], B->name, strlen(B->name)) == 0) {
            for (int j = 0; j < B->ruleCount; j++) {
                snprintf(newRulesA[newRuleCount], MAX_LENGTH, "%s%s", B->productionRules[j] + strlen(B->name), A->productionRules[i] + strlen(B->name));
                newRuleCount++;
            }
        } else {
            strcpy(newRulesA[newRuleCount++], A->productionRules[i]);
        }
    }

    A->ruleCount = newRuleCount;
    for (int i = 0; i < newRuleCount; i++) {
        strcpy(A->productionRules[i], newRulesA[i]);
    }
}

// Function to solve immediate left recursion
void solveImmediateLR(Grammar* grammar, NonTerminal* A) {
    char newName[MAX_LENGTH];
    snprintf(newName, MAX_LENGTH, "%s'", A->name);

    char alphas[MAX_RULES][MAX_LENGTH], betas[MAX_RULES][MAX_LENGTH];
    int alphaCount = 0, betaCount = 0;

    for (int i = 0; i < A->ruleCount; i++) {
        if (strncmp(A->productionRules[i], A->name, strlen(A->name)) == 0) {
            strcpy(alphas[alphaCount++], A->productionRules[i] + strlen(A->name));
        } else {
            strcpy(betas[betaCount++], A->productionRules[i]);
        }
    }

    if (alphaCount == 0) return;

    NonTerminal newNonTerminal;
    initNonTerminal(&newNonTerminal, newName);
    for (int i = 0; i < betaCount; i++) {
        char newRule[MAX_LENGTH];
        snprintf(newRule, MAX_LENGTH, "%s%s", betas[i], newName);
        addRule(&newNonTerminal, newRule);
    }

    for (int i = 0; i < alphaCount; i++) {
        char newRule[MAX_LENGTH];
        snprintf(newRule, MAX_LENGTH, "%s%s", alphas[i], newName);
        addRule(&newNonTerminal, newRule);
    }

    addRule(A, newName);
    addRule(&newNonTerminal, "ε");

    // Add the new non-terminal to the grammar
    grammar->nonTerminals[grammar->nonTerminalCount++] = newNonTerminal;
}

// Function to apply the left recursion elimination algorithm
void applyAlgorithm(Grammar* grammar) {
    for (int i = 0; i < grammar->nonTerminalCount; i++) {
        for (int j = 0; j < i; j++) {
            solveNonImmediateLR(grammar, &grammar->nonTerminals[i], &grammar->nonTerminals[j]);
        }
        solveImmediateLR(grammar, &grammar->nonTerminals[i]);
    }
}

// Function to print all the rules of grammar
void printGrammar(Grammar* grammar) {
    for (int i = 0; i < grammar->nonTerminalCount; i++) {
        printRule(&grammar->nonTerminals[i]);
    }
}

int main() {
    Grammar grammar;
    initGrammar(&grammar);

    // Input data
    addGrammarRule(&grammar, "S -> Sa | Sb | c | d");

    // Apply the left recursion elimination algorithm
    applyAlgorithm(&grammar);

    // Print the resulting grammar
    printGrammar(&grammar);

    return 0;
}
