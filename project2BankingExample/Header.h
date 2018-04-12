#pragma once
#ifndef BANKING_H
#define BANKING_H

#include <fstream>
using namespace std;

void Header(ofstream &Outfile);
void Footer(ofstream &Outfile);
bool open_input_file(ifstream &file, string filename);
bool open_output_file(ofstream &file, string filename);
void close_file(ifstream &file);
void close_file(ifstream &file);
int read_bankrecs(ifstream &bankrecs, int bank_records[50][3], int &num_records);
int read_transactions(ifstream &transcations, int bank_records[50][3], int num_records);
int find_record(int bank_records[50][3], int accountnum, int low, int high);
void bubble_sort(int A[50][3], int size, int keyindex);
void print_bankrecs(ofstream &outfile, int bank_records[50][3], int num_records);

#endif
