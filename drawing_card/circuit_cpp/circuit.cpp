#include <stdio.h>
#include <iostream>
#include <assert.h>
#include "circom.hpp"
#include "calcwit.hpp"
void Num2Bits_0_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather);
void Num2Bits_0_run(uint ctx_index,Circom_CalcWit* ctx);
void LessThan_1_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather);
void LessThan_1_run(uint ctx_index,Circom_CalcWit* ctx);
void GreaterEqThan_2_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather);
void GreaterEqThan_2_run(uint ctx_index,Circom_CalcWit* ctx);
void checkInRange_3_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather);
void checkInRange_3_run(uint ctx_index,Circom_CalcWit* ctx);
void whichSuitsItBelongsTo_4_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather);
void whichSuitsItBelongsTo_4_run(uint ctx_index,Circom_CalcWit* ctx);
void MiMCFeistel_5_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather);
void MiMCFeistel_5_run(uint ctx_index,Circom_CalcWit* ctx);
void MiMCSponge_6_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather);
void MiMCSponge_6_run(uint ctx_index,Circom_CalcWit* ctx);
void checkWhetherGivenTwoNumbersAreSameSuit_7_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather);
void checkWhetherGivenTwoNumbersAreSameSuit_7_run(uint ctx_index,Circom_CalcWit* ctx);
Circom_TemplateFunction _functionTable[8] = { 
Num2Bits_0_run,
LessThan_1_run,
GreaterEqThan_2_run,
checkInRange_3_run,
whichSuitsItBelongsTo_4_run,
MiMCFeistel_5_run,
MiMCSponge_6_run,
checkWhetherGivenTwoNumbersAreSameSuit_7_run };
uint get_main_input_signal_start() {return 2;}

uint get_main_input_signal_no() {return 3;}

uint get_total_signal_no() {return 2945;}

uint get_number_of_components() {return 54;}

uint get_size_of_input_hashmap() {return 256;}

uint get_size_of_witness() {return 2352;}

uint get_size_of_constants() {return 440;}

uint get_size_of_io_map() {return 0;}

// function declarations
// template declarations
void Num2Bits_0_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather){
ctx->componentMemory[coffset].templateId = 0;
ctx->componentMemory[coffset].templateName = "Num2Bits";
ctx->componentMemory[coffset].signalStart = soffset;
ctx->componentMemory[coffset].inputCounter = 1;
ctx->componentMemory[coffset].componentName = componentName;
ctx->componentMemory[coffset].idFather = componentFather;
ctx->componentMemory[coffset].subcomponents = new uint[0];
}

void Num2Bits_0_run(uint ctx_index,Circom_CalcWit* ctx){
FrElement* signalValues = ctx->signalValues;
u64 mySignalStart = ctx->componentMemory[ctx_index].signalStart;
std::string myTemplateName = ctx->componentMemory[ctx_index].templateName;
std::string myComponentName = ctx->componentMemory[ctx_index].componentName;
u64 myFather = ctx->componentMemory[ctx_index].idFather;
u64 myId = ctx_index;
u32* mySubcomponents = ctx->componentMemory[ctx_index].subcomponents;
FrElement* circuitConstants = ctx->circuitConstants;
std::string* listOfTemplateMessages = ctx->listOfTemplateMessages;
FrElement expaux[6];
FrElement lvar[4];
uint sub_component_aux;
{
PFrElement aux_dest = &lvar[0];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[0]);
}
{
PFrElement aux_dest = &lvar[1];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
{
PFrElement aux_dest = &lvar[2];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[2]);
}
{
PFrElement aux_dest = &lvar[3];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
Fr_lt(&expaux[0],&lvar[3],&circuitConstants[0]); // line circom 31
while(Fr_isTrue(&expaux[0])){
{
PFrElement aux_dest = &signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[3])) + 0)];
// load src
Fr_shr(&expaux[1],&signalValues[mySignalStart + 65],&lvar[3]); // line circom 32
Fr_band(&expaux[0],&expaux[1],&circuitConstants[2]); // line circom 32
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_sub(&expaux[3],&signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[3])) + 0)],&circuitConstants[2]); // line circom 33
Fr_mul(&expaux[1],&signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[3])) + 0)],&expaux[3]); // line circom 33
Fr_eq(&expaux[0],&expaux[1],&circuitConstants[1]); // line circom 33
if (!Fr_isTrue(&expaux[0])) std::cout << "Failed assert in template " << myTemplateName << " line 33. " <<  "Followed trace: " << ctx->getTrace(myId) << std::endl;
assert(Fr_isTrue(&expaux[0]));
{
PFrElement aux_dest = &lvar[1];
// load src
Fr_mul(&expaux[2],&signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[3])) + 0)],&lvar[2]); // line circom 34
Fr_add(&expaux[0],&lvar[1],&expaux[2]); // line circom 34
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
{
PFrElement aux_dest = &lvar[2];
// load src
Fr_add(&expaux[0],&lvar[2],&lvar[2]); // line circom 35
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
{
PFrElement aux_dest = &lvar[3];
// load src
Fr_add(&expaux[0],&lvar[3],&circuitConstants[2]); // line circom 31
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_lt(&expaux[0],&lvar[3],&circuitConstants[0]); // line circom 31
}
Fr_eq(&expaux[0],&lvar[1],&signalValues[mySignalStart + 65]); // line circom 38
if (!Fr_isTrue(&expaux[0])) std::cout << "Failed assert in template " << myTemplateName << " line 38. " <<  "Followed trace: " << ctx->getTrace(myId) << std::endl;
assert(Fr_isTrue(&expaux[0]));
}

void LessThan_1_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather){
ctx->componentMemory[coffset].templateId = 1;
ctx->componentMemory[coffset].templateName = "LessThan";
ctx->componentMemory[coffset].signalStart = soffset;
ctx->componentMemory[coffset].inputCounter = 2;
ctx->componentMemory[coffset].componentName = componentName;
ctx->componentMemory[coffset].idFather = componentFather;
ctx->componentMemory[coffset].subcomponents = new uint[1];
}

void LessThan_1_run(uint ctx_index,Circom_CalcWit* ctx){
FrElement* signalValues = ctx->signalValues;
u64 mySignalStart = ctx->componentMemory[ctx_index].signalStart;
std::string myTemplateName = ctx->componentMemory[ctx_index].templateName;
std::string myComponentName = ctx->componentMemory[ctx_index].componentName;
u64 myFather = ctx->componentMemory[ctx_index].idFather;
u64 myId = ctx_index;
u32* mySubcomponents = ctx->componentMemory[ctx_index].subcomponents;
FrElement* circuitConstants = ctx->circuitConstants;
std::string* listOfTemplateMessages = ctx->listOfTemplateMessages;
FrElement expaux[4];
FrElement lvar[1];
uint sub_component_aux;
{
PFrElement aux_dest = &lvar[0];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[3]);
}
{
uint aux_create = 0;
int aux_cmp_num = 0+ctx_index+1;
uint csoffset = mySignalStart+3;
for (uint i = 0; i < 1; i++) {
std::string new_cmp_name = "n2b";
mySubcomponents[aux_create+i] = aux_cmp_num;
Num2Bits_0_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 66 ;
aux_cmp_num += 1;
}
}
if (!Fr_isTrue(&circuitConstants[2])) std::cout << "Failed assert in template " << myTemplateName << " line 90. " <<  "Followed trace: " << ctx->getTrace(myId) << std::endl;
assert(Fr_isTrue(&circuitConstants[2]));
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 65];
// load src
Fr_add(&expaux[1],&signalValues[mySignalStart + 1],&circuitConstants[4]); // line circom 96
Fr_sub(&expaux[0],&expaux[1],&signalValues[mySignalStart + 2]); // line circom 96
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
// need to run sub component
assert(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
Num2Bits_0_run(mySubcomponents[cmp_index_ref],ctx);
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 0];
// load src
Fr_sub(&expaux[0],&circuitConstants[2],&ctx->signalValues[ctx->componentMemory[mySubcomponents[0]].signalStart + 64]); // line circom 98
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
}

void GreaterEqThan_2_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather){
ctx->componentMemory[coffset].templateId = 2;
ctx->componentMemory[coffset].templateName = "GreaterEqThan";
ctx->componentMemory[coffset].signalStart = soffset;
ctx->componentMemory[coffset].inputCounter = 2;
ctx->componentMemory[coffset].componentName = componentName;
ctx->componentMemory[coffset].idFather = componentFather;
ctx->componentMemory[coffset].subcomponents = new uint[1];
}

void GreaterEqThan_2_run(uint ctx_index,Circom_CalcWit* ctx){
FrElement* signalValues = ctx->signalValues;
u64 mySignalStart = ctx->componentMemory[ctx_index].signalStart;
std::string myTemplateName = ctx->componentMemory[ctx_index].templateName;
std::string myComponentName = ctx->componentMemory[ctx_index].componentName;
u64 myFather = ctx->componentMemory[ctx_index].idFather;
u64 myId = ctx_index;
u32* mySubcomponents = ctx->componentMemory[ctx_index].subcomponents;
FrElement* circuitConstants = ctx->circuitConstants;
std::string* listOfTemplateMessages = ctx->listOfTemplateMessages;
FrElement expaux[3];
FrElement lvar[1];
uint sub_component_aux;
{
PFrElement aux_dest = &lvar[0];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[3]);
}
{
uint aux_create = 0;
int aux_cmp_num = 0+ctx_index+1;
uint csoffset = mySignalStart+3;
for (uint i = 0; i < 1; i++) {
std::string new_cmp_name = "lt";
mySubcomponents[aux_create+i] = aux_cmp_num;
LessThan_1_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 69 ;
aux_cmp_num += 2;
}
}
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 1];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 2]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 2];
// load src
Fr_add(&expaux[0],&signalValues[mySignalStart + 1],&circuitConstants[2]); // line circom 138
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
// need to run sub component
assert(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
LessThan_1_run(mySubcomponents[cmp_index_ref],ctx);
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 0];
// load src
// end load src
Fr_copy(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[0]].signalStart + 0]);
}
}

void checkInRange_3_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather){
ctx->componentMemory[coffset].templateId = 3;
ctx->componentMemory[coffset].templateName = "checkInRange";
ctx->componentMemory[coffset].signalStart = soffset;
ctx->componentMemory[coffset].inputCounter = 3;
ctx->componentMemory[coffset].componentName = componentName;
ctx->componentMemory[coffset].idFather = componentFather;
ctx->componentMemory[coffset].subcomponents = new uint[2];
}

void checkInRange_3_run(uint ctx_index,Circom_CalcWit* ctx){
FrElement* signalValues = ctx->signalValues;
u64 mySignalStart = ctx->componentMemory[ctx_index].signalStart;
std::string myTemplateName = ctx->componentMemory[ctx_index].templateName;
std::string myComponentName = ctx->componentMemory[ctx_index].componentName;
u64 myFather = ctx->componentMemory[ctx_index].idFather;
u64 myId = ctx_index;
u32* mySubcomponents = ctx->componentMemory[ctx_index].subcomponents;
FrElement* circuitConstants = ctx->circuitConstants;
std::string* listOfTemplateMessages = ctx->listOfTemplateMessages;
FrElement expaux[4];
FrElement lvar[0];
uint sub_component_aux;
{
uint aux_create = 0;
int aux_cmp_num = 2+ctx_index+1;
uint csoffset = mySignalStart+73;
for (uint i = 0; i < 1; i++) {
std::string new_cmp_name = "lowThreshold";
mySubcomponents[aux_create+i] = aux_cmp_num;
GreaterEqThan_2_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 72 ;
aux_cmp_num += 3;
}
}
{
uint aux_create = 1;
int aux_cmp_num = 0+ctx_index+1;
uint csoffset = mySignalStart+4;
for (uint i = 0; i < 1; i++) {
std::string new_cmp_name = "highThreshold";
mySubcomponents[aux_create+i] = aux_cmp_num;
LessThan_1_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 69 ;
aux_cmp_num += 2;
}
}
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 1];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 1]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 2];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 2]);
}
// need to run sub component
assert(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
GreaterEqThan_2_run(mySubcomponents[cmp_index_ref],ctx);
}
{
uint cmp_index_ref = 1;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 1];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 1]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 1;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 2];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 3]);
}
// need to run sub component
assert(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
LessThan_1_run(mySubcomponents[cmp_index_ref],ctx);
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 0];
// load src
Fr_mul(&expaux[0],&ctx->signalValues[ctx->componentMemory[mySubcomponents[0]].signalStart + 0],&ctx->signalValues[ctx->componentMemory[mySubcomponents[1]].signalStart + 0]); // line circom 33
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
}

void whichSuitsItBelongsTo_4_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather){
ctx->componentMemory[coffset].templateId = 4;
ctx->componentMemory[coffset].templateName = "whichSuitsItBelongsTo";
ctx->componentMemory[coffset].signalStart = soffset;
ctx->componentMemory[coffset].inputCounter = 1;
ctx->componentMemory[coffset].componentName = componentName;
ctx->componentMemory[coffset].idFather = componentFather;
ctx->componentMemory[coffset].subcomponents = new uint[4];
}

void whichSuitsItBelongsTo_4_run(uint ctx_index,Circom_CalcWit* ctx){
FrElement* signalValues = ctx->signalValues;
u64 mySignalStart = ctx->componentMemory[ctx_index].signalStart;
std::string myTemplateName = ctx->componentMemory[ctx_index].templateName;
std::string myComponentName = ctx->componentMemory[ctx_index].componentName;
u64 myFather = ctx->componentMemory[ctx_index].idFather;
u64 myId = ctx_index;
u32* mySubcomponents = ctx->componentMemory[ctx_index].subcomponents;
FrElement* circuitConstants = ctx->circuitConstants;
std::string* listOfTemplateMessages = ctx->listOfTemplateMessages;
FrElement expaux[2];
FrElement lvar[0];
uint sub_component_aux;
{
uint aux_create = 0;
int aux_cmp_num = 18+ctx_index+1;
uint csoffset = mySignalStart+440;
for (uint i = 0; i < 1; i++) {
std::string new_cmp_name = "spades";
mySubcomponents[aux_create+i] = aux_cmp_num;
checkInRange_3_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 145 ;
aux_cmp_num += 6;
}
}
{
uint aux_create = 1;
int aux_cmp_num = 0+ctx_index+1;
uint csoffset = mySignalStart+5;
for (uint i = 0; i < 1; i++) {
std::string new_cmp_name = "clubs";
mySubcomponents[aux_create+i] = aux_cmp_num;
checkInRange_3_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 145 ;
aux_cmp_num += 6;
}
}
{
uint aux_create = 2;
int aux_cmp_num = 6+ctx_index+1;
uint csoffset = mySignalStart+150;
for (uint i = 0; i < 1; i++) {
std::string new_cmp_name = "diamonds";
mySubcomponents[aux_create+i] = aux_cmp_num;
checkInRange_3_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 145 ;
aux_cmp_num += 6;
}
}
{
uint aux_create = 3;
int aux_cmp_num = 12+ctx_index+1;
uint csoffset = mySignalStart+295;
for (uint i = 0; i < 1; i++) {
std::string new_cmp_name = "hearts";
mySubcomponents[aux_create+i] = aux_cmp_num;
checkInRange_3_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 145 ;
aux_cmp_num += 6;
}
}
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 1];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 4]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 2];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 3];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[5]);
}
// need to run sub component
assert(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
checkInRange_3_run(mySubcomponents[cmp_index_ref],ctx);
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 0];
// load src
// end load src
Fr_copy(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[0]].signalStart + 0]);
}
{
uint cmp_index_ref = 1;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 1];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 4]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 1;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 2];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[5]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 1;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 3];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[6]);
}
// need to run sub component
assert(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
checkInRange_3_run(mySubcomponents[cmp_index_ref],ctx);
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 1];
// load src
// end load src
Fr_copy(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[1]].signalStart + 0]);
}
{
uint cmp_index_ref = 2;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 1];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 4]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 2;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 2];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[6]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 2;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 3];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[7]);
}
// need to run sub component
assert(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
checkInRange_3_run(mySubcomponents[cmp_index_ref],ctx);
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 2];
// load src
// end load src
Fr_copy(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[2]].signalStart + 0]);
}
{
uint cmp_index_ref = 3;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 1];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 4]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 3;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 2];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[7]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 3;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 3];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[9]);
}
// need to run sub component
assert(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
checkInRange_3_run(mySubcomponents[cmp_index_ref],ctx);
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 3];
// load src
// end load src
Fr_copy(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[3]].signalStart + 0]);
}
}

void MiMCFeistel_5_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather){
ctx->componentMemory[coffset].templateId = 5;
ctx->componentMemory[coffset].templateName = "MiMCFeistel";
ctx->componentMemory[coffset].signalStart = soffset;
ctx->componentMemory[coffset].inputCounter = 3;
ctx->componentMemory[coffset].componentName = componentName;
ctx->componentMemory[coffset].idFather = componentFather;
ctx->componentMemory[coffset].subcomponents = new uint[0];
}

void MiMCFeistel_5_run(uint ctx_index,Circom_CalcWit* ctx){
FrElement* signalValues = ctx->signalValues;
u64 mySignalStart = ctx->componentMemory[ctx_index].signalStart;
std::string myTemplateName = ctx->componentMemory[ctx_index].templateName;
std::string myComponentName = ctx->componentMemory[ctx_index].componentName;
u64 myFather = ctx->componentMemory[ctx_index].idFather;
u64 myId = ctx_index;
u32* mySubcomponents = ctx->componentMemory[ctx_index].subcomponents;
FrElement* circuitConstants = ctx->circuitConstants;
std::string* listOfTemplateMessages = ctx->listOfTemplateMessages;
FrElement expaux[6];
FrElement lvar[223];
uint sub_component_aux;
{
PFrElement aux_dest = &lvar[0];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[11]);
}
{
PFrElement aux_dest = &lvar[1];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[12]);
}
{
PFrElement aux_dest = &lvar[2];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[13]);
}
{
PFrElement aux_dest = &lvar[3];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[14]);
}
{
PFrElement aux_dest = &lvar[4];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[15]);
}
{
PFrElement aux_dest = &lvar[5];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[17]);
}
{
PFrElement aux_dest = &lvar[6];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[19]);
}
{
PFrElement aux_dest = &lvar[7];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[21]);
}
{
PFrElement aux_dest = &lvar[8];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[23]);
}
{
PFrElement aux_dest = &lvar[9];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[25]);
}
{
PFrElement aux_dest = &lvar[10];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[27]);
}
{
PFrElement aux_dest = &lvar[11];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[29]);
}
{
PFrElement aux_dest = &lvar[12];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[31]);
}
{
PFrElement aux_dest = &lvar[13];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[33]);
}
{
PFrElement aux_dest = &lvar[14];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[34]);
}
{
PFrElement aux_dest = &lvar[15];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[36]);
}
{
PFrElement aux_dest = &lvar[16];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[38]);
}
{
PFrElement aux_dest = &lvar[17];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[40]);
}
{
PFrElement aux_dest = &lvar[18];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[42]);
}
{
PFrElement aux_dest = &lvar[19];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[44]);
}
{
PFrElement aux_dest = &lvar[20];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[46]);
}
{
PFrElement aux_dest = &lvar[21];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[48]);
}
{
PFrElement aux_dest = &lvar[22];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[50]);
}
{
PFrElement aux_dest = &lvar[23];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[52]);
}
{
PFrElement aux_dest = &lvar[24];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[54]);
}
{
PFrElement aux_dest = &lvar[25];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[56]);
}
{
PFrElement aux_dest = &lvar[26];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[58]);
}
{
PFrElement aux_dest = &lvar[27];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[59]);
}
{
PFrElement aux_dest = &lvar[28];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[61]);
}
{
PFrElement aux_dest = &lvar[29];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[63]);
}
{
PFrElement aux_dest = &lvar[30];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[65]);
}
{
PFrElement aux_dest = &lvar[31];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[67]);
}
{
PFrElement aux_dest = &lvar[32];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[69]);
}
{
PFrElement aux_dest = &lvar[33];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[71]);
}
{
PFrElement aux_dest = &lvar[34];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[73]);
}
{
PFrElement aux_dest = &lvar[35];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[75]);
}
{
PFrElement aux_dest = &lvar[36];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[77]);
}
{
PFrElement aux_dest = &lvar[37];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[79]);
}
{
PFrElement aux_dest = &lvar[38];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[81]);
}
{
PFrElement aux_dest = &lvar[39];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[83]);
}
{
PFrElement aux_dest = &lvar[40];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[84]);
}
{
PFrElement aux_dest = &lvar[41];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[86]);
}
{
PFrElement aux_dest = &lvar[42];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[88]);
}
{
PFrElement aux_dest = &lvar[43];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[90]);
}
{
PFrElement aux_dest = &lvar[44];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[92]);
}
{
PFrElement aux_dest = &lvar[45];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[94]);
}
{
PFrElement aux_dest = &lvar[46];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[96]);
}
{
PFrElement aux_dest = &lvar[47];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[98]);
}
{
PFrElement aux_dest = &lvar[48];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[100]);
}
{
PFrElement aux_dest = &lvar[49];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[102]);
}
{
PFrElement aux_dest = &lvar[50];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[104]);
}
{
PFrElement aux_dest = &lvar[51];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[106]);
}
{
PFrElement aux_dest = &lvar[52];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[108]);
}
{
PFrElement aux_dest = &lvar[53];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[109]);
}
{
PFrElement aux_dest = &lvar[54];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[111]);
}
{
PFrElement aux_dest = &lvar[55];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[113]);
}
{
PFrElement aux_dest = &lvar[56];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[115]);
}
{
PFrElement aux_dest = &lvar[57];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[117]);
}
{
PFrElement aux_dest = &lvar[58];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[119]);
}
{
PFrElement aux_dest = &lvar[59];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[121]);
}
{
PFrElement aux_dest = &lvar[60];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[123]);
}
{
PFrElement aux_dest = &lvar[61];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[125]);
}
{
PFrElement aux_dest = &lvar[62];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[127]);
}
{
PFrElement aux_dest = &lvar[63];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[129]);
}
{
PFrElement aux_dest = &lvar[64];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[131]);
}
{
PFrElement aux_dest = &lvar[65];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[132]);
}
{
PFrElement aux_dest = &lvar[66];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[133]);
}
{
PFrElement aux_dest = &lvar[67];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[135]);
}
{
PFrElement aux_dest = &lvar[68];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[137]);
}
{
PFrElement aux_dest = &lvar[69];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[139]);
}
{
PFrElement aux_dest = &lvar[70];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[141]);
}
{
PFrElement aux_dest = &lvar[71];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[143]);
}
{
PFrElement aux_dest = &lvar[72];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[145]);
}
{
PFrElement aux_dest = &lvar[73];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[147]);
}
{
PFrElement aux_dest = &lvar[74];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[149]);
}
{
PFrElement aux_dest = &lvar[75];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[151]);
}
{
PFrElement aux_dest = &lvar[76];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[153]);
}
{
PFrElement aux_dest = &lvar[77];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[155]);
}
{
PFrElement aux_dest = &lvar[78];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[157]);
}
{
PFrElement aux_dest = &lvar[79];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[159]);
}
{
PFrElement aux_dest = &lvar[80];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[161]);
}
{
PFrElement aux_dest = &lvar[81];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[163]);
}
{
PFrElement aux_dest = &lvar[82];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[165]);
}
{
PFrElement aux_dest = &lvar[83];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[167]);
}
{
PFrElement aux_dest = &lvar[84];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[169]);
}
{
PFrElement aux_dest = &lvar[85];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[171]);
}
{
PFrElement aux_dest = &lvar[86];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[173]);
}
{
PFrElement aux_dest = &lvar[87];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[175]);
}
{
PFrElement aux_dest = &lvar[88];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[177]);
}
{
PFrElement aux_dest = &lvar[89];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[179]);
}
{
PFrElement aux_dest = &lvar[90];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[181]);
}
{
PFrElement aux_dest = &lvar[91];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[183]);
}
{
PFrElement aux_dest = &lvar[92];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[185]);
}
{
PFrElement aux_dest = &lvar[93];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[187]);
}
{
PFrElement aux_dest = &lvar[94];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[189]);
}
{
PFrElement aux_dest = &lvar[95];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[191]);
}
{
PFrElement aux_dest = &lvar[96];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[193]);
}
{
PFrElement aux_dest = &lvar[97];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[195]);
}
{
PFrElement aux_dest = &lvar[98];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[197]);
}
{
PFrElement aux_dest = &lvar[99];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[199]);
}
{
PFrElement aux_dest = &lvar[100];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[201]);
}
{
PFrElement aux_dest = &lvar[101];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[203]);
}
{
PFrElement aux_dest = &lvar[102];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[205]);
}
{
PFrElement aux_dest = &lvar[103];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[207]);
}
{
PFrElement aux_dest = &lvar[104];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[209]);
}
{
PFrElement aux_dest = &lvar[105];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[211]);
}
{
PFrElement aux_dest = &lvar[106];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[213]);
}
{
PFrElement aux_dest = &lvar[107];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[215]);
}
{
PFrElement aux_dest = &lvar[108];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[217]);
}
{
PFrElement aux_dest = &lvar[109];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[219]);
}
{
PFrElement aux_dest = &lvar[110];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[221]);
}
{
PFrElement aux_dest = &lvar[111];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[223]);
}
{
PFrElement aux_dest = &lvar[112];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[225]);
}
{
PFrElement aux_dest = &lvar[113];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[227]);
}
{
PFrElement aux_dest = &lvar[114];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[229]);
}
{
PFrElement aux_dest = &lvar[115];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[231]);
}
{
PFrElement aux_dest = &lvar[116];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[233]);
}
{
PFrElement aux_dest = &lvar[117];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[235]);
}
{
PFrElement aux_dest = &lvar[118];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[237]);
}
{
PFrElement aux_dest = &lvar[119];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[239]);
}
{
PFrElement aux_dest = &lvar[120];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[241]);
}
{
PFrElement aux_dest = &lvar[121];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[243]);
}
{
PFrElement aux_dest = &lvar[122];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[245]);
}
{
PFrElement aux_dest = &lvar[123];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[247]);
}
{
PFrElement aux_dest = &lvar[124];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[249]);
}
{
PFrElement aux_dest = &lvar[125];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[251]);
}
{
PFrElement aux_dest = &lvar[126];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[253]);
}
{
PFrElement aux_dest = &lvar[127];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[255]);
}
{
PFrElement aux_dest = &lvar[128];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[257]);
}
{
PFrElement aux_dest = &lvar[129];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[259]);
}
{
PFrElement aux_dest = &lvar[130];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[261]);
}
{
PFrElement aux_dest = &lvar[131];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[263]);
}
{
PFrElement aux_dest = &lvar[132];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[265]);
}
{
PFrElement aux_dest = &lvar[133];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[267]);
}
{
PFrElement aux_dest = &lvar[134];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[269]);
}
{
PFrElement aux_dest = &lvar[135];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[271]);
}
{
PFrElement aux_dest = &lvar[136];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[273]);
}
{
PFrElement aux_dest = &lvar[137];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[275]);
}
{
PFrElement aux_dest = &lvar[138];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[277]);
}
{
PFrElement aux_dest = &lvar[139];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[279]);
}
{
PFrElement aux_dest = &lvar[140];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[281]);
}
{
PFrElement aux_dest = &lvar[141];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[283]);
}
{
PFrElement aux_dest = &lvar[142];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[285]);
}
{
PFrElement aux_dest = &lvar[143];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[287]);
}
{
PFrElement aux_dest = &lvar[144];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[289]);
}
{
PFrElement aux_dest = &lvar[145];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[291]);
}
{
PFrElement aux_dest = &lvar[146];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[293]);
}
{
PFrElement aux_dest = &lvar[147];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[295]);
}
{
PFrElement aux_dest = &lvar[148];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[297]);
}
{
PFrElement aux_dest = &lvar[149];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[299]);
}
{
PFrElement aux_dest = &lvar[150];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[301]);
}
{
PFrElement aux_dest = &lvar[151];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[303]);
}
{
PFrElement aux_dest = &lvar[152];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[305]);
}
{
PFrElement aux_dest = &lvar[153];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[307]);
}
{
PFrElement aux_dest = &lvar[154];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[309]);
}
{
PFrElement aux_dest = &lvar[155];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[311]);
}
{
PFrElement aux_dest = &lvar[156];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[313]);
}
{
PFrElement aux_dest = &lvar[157];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[315]);
}
{
PFrElement aux_dest = &lvar[158];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[317]);
}
{
PFrElement aux_dest = &lvar[159];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[319]);
}
{
PFrElement aux_dest = &lvar[160];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[321]);
}
{
PFrElement aux_dest = &lvar[161];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[323]);
}
{
PFrElement aux_dest = &lvar[162];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[325]);
}
{
PFrElement aux_dest = &lvar[163];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[327]);
}
{
PFrElement aux_dest = &lvar[164];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[329]);
}
{
PFrElement aux_dest = &lvar[165];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[331]);
}
{
PFrElement aux_dest = &lvar[166];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[333]);
}
{
PFrElement aux_dest = &lvar[167];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[335]);
}
{
PFrElement aux_dest = &lvar[168];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[337]);
}
{
PFrElement aux_dest = &lvar[169];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[339]);
}
{
PFrElement aux_dest = &lvar[170];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[341]);
}
{
PFrElement aux_dest = &lvar[171];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[343]);
}
{
PFrElement aux_dest = &lvar[172];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[345]);
}
{
PFrElement aux_dest = &lvar[173];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[347]);
}
{
PFrElement aux_dest = &lvar[174];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[349]);
}
{
PFrElement aux_dest = &lvar[175];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[351]);
}
{
PFrElement aux_dest = &lvar[176];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[353]);
}
{
PFrElement aux_dest = &lvar[177];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[355]);
}
{
PFrElement aux_dest = &lvar[178];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[357]);
}
{
PFrElement aux_dest = &lvar[179];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[359]);
}
{
PFrElement aux_dest = &lvar[180];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[361]);
}
{
PFrElement aux_dest = &lvar[181];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[363]);
}
{
PFrElement aux_dest = &lvar[182];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[365]);
}
{
PFrElement aux_dest = &lvar[183];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[367]);
}
{
PFrElement aux_dest = &lvar[184];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[369]);
}
{
PFrElement aux_dest = &lvar[185];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[371]);
}
{
PFrElement aux_dest = &lvar[186];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[373]);
}
{
PFrElement aux_dest = &lvar[187];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[375]);
}
{
PFrElement aux_dest = &lvar[188];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[377]);
}
{
PFrElement aux_dest = &lvar[189];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[379]);
}
{
PFrElement aux_dest = &lvar[190];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[381]);
}
{
PFrElement aux_dest = &lvar[191];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[383]);
}
{
PFrElement aux_dest = &lvar[192];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[385]);
}
{
PFrElement aux_dest = &lvar[193];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[387]);
}
{
PFrElement aux_dest = &lvar[194];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[389]);
}
{
PFrElement aux_dest = &lvar[195];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[391]);
}
{
PFrElement aux_dest = &lvar[196];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[393]);
}
{
PFrElement aux_dest = &lvar[197];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[395]);
}
{
PFrElement aux_dest = &lvar[198];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[397]);
}
{
PFrElement aux_dest = &lvar[199];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[399]);
}
{
PFrElement aux_dest = &lvar[200];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[401]);
}
{
PFrElement aux_dest = &lvar[201];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[403]);
}
{
PFrElement aux_dest = &lvar[202];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[405]);
}
{
PFrElement aux_dest = &lvar[203];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[407]);
}
{
PFrElement aux_dest = &lvar[204];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[409]);
}
{
PFrElement aux_dest = &lvar[205];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[411]);
}
{
PFrElement aux_dest = &lvar[206];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[413]);
}
{
PFrElement aux_dest = &lvar[207];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[415]);
}
{
PFrElement aux_dest = &lvar[208];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[417]);
}
{
PFrElement aux_dest = &lvar[209];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[419]);
}
{
PFrElement aux_dest = &lvar[210];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[421]);
}
{
PFrElement aux_dest = &lvar[211];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[423]);
}
{
PFrElement aux_dest = &lvar[212];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[425]);
}
{
PFrElement aux_dest = &lvar[213];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[427]);
}
{
PFrElement aux_dest = &lvar[214];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[429]);
}
{
PFrElement aux_dest = &lvar[215];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[431]);
}
{
PFrElement aux_dest = &lvar[216];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[433]);
}
{
PFrElement aux_dest = &lvar[217];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[435]);
}
{
PFrElement aux_dest = &lvar[218];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[437]);
}
{
PFrElement aux_dest = &lvar[221];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
Fr_lt(&expaux[0],&lvar[221],&circuitConstants[11]); // line circom 275
while(Fr_isTrue(&expaux[0])){
Fr_eq(&expaux[1],&lvar[221],&circuitConstants[1]); // line circom 276
Fr_eq(&expaux[2],&lvar[221],&circuitConstants[438]); // line circom 276
Fr_lor(&expaux[0],&expaux[1],&expaux[2]); // line circom 276
if(Fr_isTrue(&expaux[0])){
{
PFrElement aux_dest = &lvar[220];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
}else{
{
PFrElement aux_dest = &lvar[220];
// load src
Fr_sub(&expaux[0],&lvar[221],&circuitConstants[2]); // line circom 279
// end load src
Fr_copy(aux_dest,&lvar[((1 * Fr_toInt(&expaux[0])) + 1)]);
}
}
Fr_eq(&expaux[0],&lvar[221],&circuitConstants[1]); // line circom 281
if(Fr_isTrue(&expaux[0])){
{
PFrElement aux_dest = &lvar[219];
// load src
Fr_add(&expaux[0],&signalValues[mySignalStart + 4],&signalValues[mySignalStart + 2]); // line circom 281
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
}else{
{
PFrElement aux_dest = &lvar[219];
// load src
Fr_sub(&expaux[3],&lvar[221],&circuitConstants[2]); // line circom 281
Fr_add(&expaux[1],&signalValues[mySignalStart + 4],&signalValues[mySignalStart + ((1 * Fr_toInt(&expaux[3])) + 445)]); // line circom 281
Fr_add(&expaux[0],&expaux[1],&lvar[220]); // line circom 281
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
}
{
PFrElement aux_dest = &signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[221])) + 5)];
// load src
Fr_mul(&expaux[0],&lvar[219],&lvar[219]); // line circom 282
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
{
PFrElement aux_dest = &signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[221])) + 225)];
// load src
Fr_mul(&expaux[0],&signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[221])) + 5)],&signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[221])) + 5)]); // line circom 283
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_lt(&expaux[0],&lvar[221],&circuitConstants[438]); // line circom 284
if(Fr_isTrue(&expaux[0])){
Fr_eq(&expaux[0],&lvar[221],&circuitConstants[1]); // line circom 285
if(Fr_isTrue(&expaux[0])){
{
PFrElement aux_dest = &lvar[222];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 3]);
}
}else{
{
PFrElement aux_dest = &lvar[222];
// load src
Fr_sub(&expaux[0],&lvar[221],&circuitConstants[2]); // line circom 285
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + ((1 * Fr_toInt(&expaux[0])) + 664)]);
}
}
{
PFrElement aux_dest = &signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[221])) + 445)];
// load src
Fr_mul(&expaux[2],&signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[221])) + 225)],&lvar[219]); // line circom 286
Fr_add(&expaux[0],&lvar[222],&expaux[2]); // line circom 286
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_eq(&expaux[0],&lvar[221],&circuitConstants[1]); // line circom 287
if(Fr_isTrue(&expaux[0])){
{
PFrElement aux_dest = &signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[221])) + 664)];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 2]);
}
}else{
{
PFrElement aux_dest = &signalValues[mySignalStart + ((1 * Fr_toInt(&lvar[221])) + 664)];
// load src
Fr_sub(&expaux[0],&lvar[221],&circuitConstants[2]); // line circom 287
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + ((1 * Fr_toInt(&expaux[0])) + 445)]);
}
}
}else{
{
PFrElement aux_dest = &signalValues[mySignalStart + 1];
// load src
Fr_mul(&expaux[2],&signalValues[mySignalStart + 444],&lvar[219]); // line circom 289
Fr_add(&expaux[0],&signalValues[mySignalStart + 882],&expaux[2]); // line circom 289
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 0];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 663]);
}
}
{
PFrElement aux_dest = &lvar[221];
// load src
Fr_add(&expaux[0],&lvar[221],&circuitConstants[2]); // line circom 275
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_lt(&expaux[0],&lvar[221],&circuitConstants[11]); // line circom 275
}
}

void MiMCSponge_6_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather){
ctx->componentMemory[coffset].templateId = 6;
ctx->componentMemory[coffset].templateName = "MiMCSponge";
ctx->componentMemory[coffset].signalStart = soffset;
ctx->componentMemory[coffset].inputCounter = 3;
ctx->componentMemory[coffset].componentName = componentName;
ctx->componentMemory[coffset].idFather = componentFather;
ctx->componentMemory[coffset].subcomponents = new uint[2];
}

void MiMCSponge_6_run(uint ctx_index,Circom_CalcWit* ctx){
FrElement* signalValues = ctx->signalValues;
u64 mySignalStart = ctx->componentMemory[ctx_index].signalStart;
std::string myTemplateName = ctx->componentMemory[ctx_index].templateName;
std::string myComponentName = ctx->componentMemory[ctx_index].componentName;
u64 myFather = ctx->componentMemory[ctx_index].idFather;
u64 myId = ctx_index;
u32* mySubcomponents = ctx->componentMemory[ctx_index].subcomponents;
FrElement* circuitConstants = ctx->circuitConstants;
std::string* listOfTemplateMessages = ctx->listOfTemplateMessages;
FrElement expaux[3];
FrElement lvar[4];
uint sub_component_aux;
{
PFrElement aux_dest = &lvar[0];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[8]);
}
{
PFrElement aux_dest = &lvar[1];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[11]);
}
{
PFrElement aux_dest = &lvar[2];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[2]);
}
{
uint aux_create = 0;
int aux_cmp_num = 0+ctx_index+1;
uint csoffset = mySignalStart+4;
uint aux_dimensions[1] = {2};
for (uint i = 0; i < 2; i++) {
std::string new_cmp_name = "S"+ctx->generate_position_array(aux_dimensions, 1, i);
mySubcomponents[aux_create+i] = aux_cmp_num;
MiMCFeistel_5_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 883 ;
aux_cmp_num += 1;
}
}
{
PFrElement aux_dest = &lvar[3];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
Fr_lt(&expaux[0],&lvar[3],&circuitConstants[8]); // line circom 16
while(Fr_isTrue(&expaux[0])){
{
uint cmp_index_ref = ((1 * Fr_toInt(&lvar[3])) + 0);
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 4];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 3]);
}
// run sub component if needed
if(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter)){
MiMCFeistel_5_run(mySubcomponents[cmp_index_ref],ctx);

}
}
Fr_eq(&expaux[0],&lvar[3],&circuitConstants[1]); // line circom 19
if(Fr_isTrue(&expaux[0])){
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 2];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 1]);
}
// run sub component if needed
if(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter)){
MiMCFeistel_5_run(mySubcomponents[cmp_index_ref],ctx);

}
}
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 3];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
// run sub component if needed
if(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter)){
MiMCFeistel_5_run(mySubcomponents[cmp_index_ref],ctx);

}
}
}else{
{
uint cmp_index_ref = 1;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 2];
// load src
Fr_add(&expaux[0],&ctx->signalValues[ctx->componentMemory[mySubcomponents[0]].signalStart + 0],&signalValues[mySignalStart + 2]); // line circom 23
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
// run sub component if needed
if(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter)){
MiMCFeistel_5_run(mySubcomponents[cmp_index_ref],ctx);

}
}
{
uint cmp_index_ref = 1;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 3];
// load src
// end load src
Fr_copy(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[0]].signalStart + 1]);
}
// run sub component if needed
if(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter)){
MiMCFeistel_5_run(mySubcomponents[cmp_index_ref],ctx);

}
}
}
{
PFrElement aux_dest = &lvar[3];
// load src
Fr_add(&expaux[0],&lvar[3],&circuitConstants[2]); // line circom 16
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_lt(&expaux[0],&lvar[3],&circuitConstants[8]); // line circom 16
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 0];
// load src
// end load src
Fr_copy(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[1]].signalStart + 0]);
}
{
PFrElement aux_dest = &lvar[3];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
}

void checkWhetherGivenTwoNumbersAreSameSuit_7_create(uint soffset,uint coffset,Circom_CalcWit* ctx,std::string componentName,uint componentFather){
ctx->componentMemory[coffset].templateId = 7;
ctx->componentMemory[coffset].templateName = "checkWhetherGivenTwoNumbersAreSameSuit";
ctx->componentMemory[coffset].signalStart = soffset;
ctx->componentMemory[coffset].inputCounter = 3;
ctx->componentMemory[coffset].componentName = componentName;
ctx->componentMemory[coffset].idFather = componentFather;
ctx->componentMemory[coffset].subcomponents = new uint[3];
}

void checkWhetherGivenTwoNumbersAreSameSuit_7_run(uint ctx_index,Circom_CalcWit* ctx){
FrElement* signalValues = ctx->signalValues;
u64 mySignalStart = ctx->componentMemory[ctx_index].signalStart;
std::string myTemplateName = ctx->componentMemory[ctx_index].templateName;
std::string myComponentName = ctx->componentMemory[ctx_index].componentName;
u64 myFather = ctx->componentMemory[ctx_index].idFather;
u64 myId = ctx_index;
u32* mySubcomponents = ctx->componentMemory[ctx_index].subcomponents;
FrElement* circuitConstants = ctx->circuitConstants;
std::string* listOfTemplateMessages = ctx->listOfTemplateMessages;
FrElement expaux[4];
FrElement lvar[1];
uint sub_component_aux;
{
uint aux_create = 0;
int aux_cmp_num = 0+ctx_index+1;
uint csoffset = mySignalStart+4;
for (uint i = 0; i < 1; i++) {
std::string new_cmp_name = "firstCardSuitCandidates";
mySubcomponents[aux_create+i] = aux_cmp_num;
whichSuitsItBelongsTo_4_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 585 ;
aux_cmp_num += 25;
}
}
{
uint aux_create = 1;
int aux_cmp_num = 28+ctx_index+1;
uint csoffset = mySignalStart+2359;
for (uint i = 0; i < 1; i++) {
std::string new_cmp_name = "secondCardSuiteCandidates";
mySubcomponents[aux_create+i] = aux_cmp_num;
whichSuitsItBelongsTo_4_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 585 ;
aux_cmp_num += 25;
}
}
{
uint aux_create = 2;
int aux_cmp_num = 25+ctx_index+1;
uint csoffset = mySignalStart+589;
for (uint i = 0; i < 1; i++) {
std::string new_cmp_name = "mimc";
mySubcomponents[aux_create+i] = aux_cmp_num;
MiMCSponge_6_create(csoffset,aux_cmp_num,ctx,new_cmp_name,myId);
csoffset += 1770 ;
aux_cmp_num += 3;
}
}
Fr_geq(&expaux[0],&signalValues[mySignalStart + 1],&circuitConstants[1]); // line circom 73
if (!Fr_isTrue(&expaux[0])) std::cout << "Failed assert in template " << myTemplateName << " line 73. " <<  "Followed trace: " << ctx->getTrace(myId) << std::endl;
assert(Fr_isTrue(&expaux[0]));
Fr_lt(&expaux[0],&signalValues[mySignalStart + 1],&circuitConstants[9]); // line circom 74
if (!Fr_isTrue(&expaux[0])) std::cout << "Failed assert in template " << myTemplateName << " line 74. " <<  "Followed trace: " << ctx->getTrace(myId) << std::endl;
assert(Fr_isTrue(&expaux[0]));
Fr_geq(&expaux[0],&signalValues[mySignalStart + 2],&circuitConstants[1]); // line circom 75
if (!Fr_isTrue(&expaux[0])) std::cout << "Failed assert in template " << myTemplateName << " line 75. " <<  "Followed trace: " << ctx->getTrace(myId) << std::endl;
assert(Fr_isTrue(&expaux[0]));
Fr_lt(&expaux[0],&signalValues[mySignalStart + 2],&circuitConstants[9]); // line circom 76
if (!Fr_isTrue(&expaux[0])) std::cout << "Failed assert in template " << myTemplateName << " line 76. " <<  "Followed trace: " << ctx->getTrace(myId) << std::endl;
assert(Fr_isTrue(&expaux[0]));
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 4];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 1]);
}
// need to run sub component
assert(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
whichSuitsItBelongsTo_4_run(mySubcomponents[cmp_index_ref],ctx);
}
{
uint cmp_index_ref = 1;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 4];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 2]);
}
// need to run sub component
assert(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
whichSuitsItBelongsTo_4_run(mySubcomponents[cmp_index_ref],ctx);
}
{
PFrElement aux_dest = &lvar[0];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
Fr_lt(&expaux[0],&lvar[0],&circuitConstants[16]); // line circom 84
while(Fr_isTrue(&expaux[0])){
Fr_eq(&expaux[0],&ctx->signalValues[ctx->componentMemory[mySubcomponents[0]].signalStart + ((1 * Fr_toInt(&lvar[0])) + 0)],&ctx->signalValues[ctx->componentMemory[mySubcomponents[1]].signalStart + ((1 * Fr_toInt(&lvar[0])) + 0)]); // line circom 85
if (!Fr_isTrue(&expaux[0])) std::cout << "Failed assert in template " << myTemplateName << " line 85. " <<  "Followed trace: " << ctx->getTrace(myId) << std::endl;
assert(Fr_isTrue(&expaux[0]));
{
PFrElement aux_dest = &lvar[0];
// load src
Fr_add(&expaux[0],&lvar[0],&circuitConstants[2]); // line circom 84
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_lt(&expaux[0],&lvar[0],&circuitConstants[16]); // line circom 84
}
{
uint cmp_index_ref = 2;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 1];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 1]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 2;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 2];
// load src
// end load src
Fr_copy(aux_dest,&signalValues[mySignalStart + 3]);
}
// no need to run sub component
assert(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter);
}
{
uint cmp_index_ref = 2;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 3];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[2]);
}
// need to run sub component
assert(!(--ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
MiMCSponge_6_run(mySubcomponents[cmp_index_ref],ctx);
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 0];
// load src
// end load src
Fr_copy(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[2]].signalStart + 0]);
}
}

void run(Circom_CalcWit* ctx){
checkWhetherGivenTwoNumbersAreSameSuit_7_create(1,0,ctx,"main",0);
checkWhetherGivenTwoNumbersAreSameSuit_7_run(0,ctx);
}

