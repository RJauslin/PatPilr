#include <Rcpp.h>
#include <cmath>
#include <string>

using namespace Rcpp;
using namespace std;

//' CheckPrimer
//'
//' blabla
//'
//' @param pr2 pr2 data.frame
//' @param primer1 vector of all possible primer 1 to consider
//' @param primer2 vector of all possible primer 2 to consider
//'
//' @export
//' @useDynLib pipelineR
//' @importFrom Rcpp sourceCpp
// [[Rcpp::export]]
Rcpp::List CheckPrimer(Rcpp::List pr2,
                     Rcpp::StringVector primer1,
                     Rcpp::StringVector primer2,
                     int l_min,
                     int l_max)
  {

  // OUTPUT
  int n = pr2.size();
  int m1 = primer1.size();
  int m2 = primer2.size();
  Rcpp::NumericVector out;
  Rcpp::NumericVector dbl;
  Rcpp::StringVector out2;

  // std::vector<std::string> primer2_std(primer2.size());
  // primer2_std = primer2;

  // Rcpp::DataFrame out;
  // std::cout << m1 << m2 << std::endl;
  for(int i = 0; i < n; i++) {
    // insert pr2 in a std::string
    std::string tmp = pr2(i);
    if (i % 10000 == 0){
      std::cout<<i<<std::endl;
    }
    // LOOP ON THE FIRST PRIMER
    for(int j = 0; j < m1; j++){
      //CHECK IF PRIMER1 IS INSIDE TMP
      if (tmp.find(primer1[j]) != std::string::npos) {
        // std::cout << "found primer1 !" << '\n';
        std::size_t pos1 = tmp.find(primer1[j]);
        // LOOP ON THE FIRST PRIMER
        for(int k = 0; k < m2; k++){

          //CHECK IF PRIMER1 IS INSIDE TMP
          if (tmp.find(primer2[k]) != std::string::npos) {

            int len_pos2 = primer2(k).size();

            std::size_t pos2 = tmp.find(primer2[k]);
            std::size_t len = pos2 + len_pos2 - pos1;
            std::string str3 = tmp.substr (pos1,len);

            if (std::find(out2.begin(), out2.end(), str3) != out2.end()){
              dbl.push_back((i+1));
             break;
            }else{
              if(str3.length() >= l_min & str3.length() <= l_max){
                out2.push_back(str3);
                out.push_back((i+1));
                break;
              }else{
                break;
              }
            }
            // std::cout << pos1 << ' ' << pos2 << '\n';
            // std::cout << str3 << '\n';
            // std::cout << "found primer2 !" << '\n';

          }
        }
        break;
      }
    }
  }
  return Rcpp::List::create(Rcpp::Named("Fasta") = Rcpp::DataFrame::create( Named("index")= out, Named("seq") = out2),
                            Rcpp::Named("doublons") = Rcpp::DataFrame::create(Named("doublons") = dbl));
  // return(out);
}












// Rcpp::List Algo5Rcpp(Rcpp::List survsig,
//                         int N,
//                         double d_t,
//                         int Nt,
//                         Rcpp::NumericVector V_c,
//                         Rcpp::NumericVector param2,
//                         Rcpp::NumericVector param1,
//                         Rcpp::NumericVector paramRepair){
//   //CODE INTIALIZATION
//   int K = V_c.size();
//   int C = sum(V_c);
//
//
//
//   // NumericVector Vs(C,2.0);
//   Rcpp::NumericVector Vr(Nt,0.0);
//   // Rcpp::NumericVector CompoIndex = NumericVector::create(0.0,0.0,0.0,1.0,1.0,1.0);
//   Rcpp::NumericVector CompoIndex = NumericVector::create(0.0,0.0,1.0,1.0);
//   Rcpp::NumericVector V_c_original(V_c);
//   Rcpp::NumericVector Vt(C);
//
//   int z(0);
//   double tz(100000.0);
//   int u(0);
//
//   //FOR LOOP
//   int n(0);
//   int i(0);
//   int j(0);
//   int index(0);
//
//   int s(0);
//   int t(0);
//   Rcpp::NumericVector prob = survsig["Probability"];
//   Rcpp::NumericVector a = survsig["T1"];
//   Rcpp::NumericVector b = survsig["T2"];
//
//   for(n = 0; n < N; n++){
//     std::cout<<n<<std::endl;
//     // std::cout<<V_c<<std::endl;
//     u = 0;
//     // Rcpp::NumericVector V_c(2,3.0);
//     Rcpp::NumericVector V_c(2,2.0);
//     for(i = 0; i< C; i ++){
//       Vt[i] = R::rweibull(param2[0],param2[1]);
//       // std::cout<<Vr[0]<<std::endl;
//       // Vr[0] = Vr[0] + Vt[i];
//     }
//     Rcpp::NumericVector Vs(C,2.0);
//     double t_old(0.0);
//     while( min(Vt) <= Nt*d_t){
//       tz = max(Vt);
//       // FIND MIN AND RETURN THE INDEX
//       for(int j = 0; j< 4; j++){
//         if( Vt[j] < tz){
//           tz = Vt[j];
//           z = j;
//         }
//       }
//
//       int k(CompoIndex[z]);
//
//
//       for(int s = 0;s<=a.size();s++){
//         if(a[s] == V_c[0]){
//           for(int t = 0;t<=s;t++){
//             if(b[t] == V_c[1]){
//               index = t;
//             }
//           }
//         }
//       }
//       while( (t_old <= u*d_t) and (u*d_t < tz)){
//           Vr[u] = Vr[u] + prob[index];
//           // std::cout<<prob[index]<<std::endl;
//           u++;
//           // return u;
//       }
//
//
//       if(Vs[z] == 2){
//         Vs[z] = 1;
//         Vt[z] = tz + R::rweibull(param1[0],param1[1]);
//       }else if(Vs[z] == 1){
//         Vs[z] = 0;
//         V_c[k] = V_c[k] - 1;
//         Vt[z] = tz + R::rweibull(paramRepair[0],paramRepair[1]);
//       }else if(Vs[z] == 0){
//         Vs[z] = 1;
//         if(V_c[k] != 3){
//           V_c[k] = V_c[k] + 1;
//         }
//         Vt[z] = tz + R::rweibull(param1[0],param1[1]);
//       }
//       t_old = tz;
//
//
//
//       // std::cout<<V_c<<std::endl;
//       for(int s = 0;s<=a.size();s++){
//         if(a[s] == V_c[0]){
//           for(int t = 0;t<=s;t++){
//             if(b[t] == V_c[1]){
//               index = t;
//             }
//           }
//         }
//       }
//
//       // ENSURE THE FINAL STEP IS ACTUALLY ADD
//       if(min(Vt) > Nt*d_t){
//         while(u*d_t < Nt*d_t){
//          Vr[u] = Vr[u] + prob[index];
//          u++;
//         }
//       }
//     }
//   }
//   return(Vr);
// }


// You can include R code blocks in C++ files processed with sourceCpp
// (useful for testing and development). The R code will be automatically
// run after the compilation.
//
//
// /*** R
// # C:\Users\Raphael\Documents\PDM\MasterProjectPackage\MasterProjectPackage\inst\Workflow_Example
//  # sourceCpp("C:/Users/Raphael/Documents/PDM/MasterProjectPackage/MasterProjectPackage/inst/Algo5Rcpp.cpp")
// # g <- graph.formula(s-1-2-3-t,s-1-4-6-t,4-5-6,2-5-3)
// # g <- setCompTypes(g,list("T1" = c(1,2,3),"T2"= c(4,5,6)))
// # survsig <- computeSystemSurvivalSignature(g)
// # V_c <- c(3,3)
// # N <- 1000
// # Nt <- 1000
// # d_t <- 0.1
// #
// # Simul3 <- Algo5Rcpp(survsig,N,d_t,Nt,V_c,
// #                      param2 = c(10,70),
// #                      param1 = c(4,1.2),
// #                      paramRepair = c(0.5,0.01))
// # plot(Simul3)
//
//  # Simul3 <- Algo5Rcpp(survsig,N,d_t,Nt,V_c,
//  # F_kInput2,
//  # F_kInput1,
//  # F_kRepair,
//  # paramInput2,
//  # paramInput1,
//  # paramRepair)
//  # plot(Simul3)
// */
