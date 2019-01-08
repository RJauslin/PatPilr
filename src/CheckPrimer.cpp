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
//' @param l_min bla
//' @param l_max bla
//' @param keepPrimer asdfjk
//'
//' @export
//' @useDynLib PatPilr
//' @importFrom Rcpp sourceCpp
// [[Rcpp::export]]
Rcpp::List CheckPrimer(Rcpp::List pr2,
                     Rcpp::StringVector primer1,
                     Rcpp::StringVector primer2,
                     int l_min,
                     int l_max,
                     bool keepPrimer)
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
      Rcout<<i<<std::endl;
    }
    // LOOP ON THE FIRST PRIMER
    for(int j = 0; j < m1; j++){
      // CHECK IF PRIMER1 IS INSIDE TMP
      if(tmp.find(primer1[j]) != std::string::npos){

        std::size_t pos1 = tmp.find(primer1[j]);
        int len_pos1 = primer1[j].size();

        // LOOP ON THE FIRST PRIMER
        for(int k = 0; k < m2; k++){
          // CHECK IF PRIMER1 IS INSIDE TMP
          if(tmp.find(primer2[k]) != std::string::npos){

            int len_pos2 = primer2(k).size();
            std::size_t pos2 = tmp.find(primer2[k]);
            std::size_t len = pos2 + len_pos2 - pos1;
            std::string str3 = tmp.substr (pos1,len);
            std::string strSeq = tmp.substr(pos1 + len_pos1,len - len_pos1 -len_pos2);
            if(keepPrimer == false){
              str3 = tmp.substr(pos1 + len_pos1,len - len_pos1 -len_pos2);
            }
            if(std::find(out2.begin(), out2.end(), str3) != out2.end()){
              dbl.push_back((i+1));
            }else{
              if(strSeq.length() >= l_min & strSeq.length() <= l_max){
                  out2.push_back(str3);
                  out.push_back((i+1));
              }
            }
          }
        }
      }
    }
  }
  return Rcpp::List::create(Rcpp::Named("Fasta") = Rcpp::DataFrame::create( Named("index")= out, Named("seq") = out2),
                            Rcpp::Named("doublons") = Rcpp::DataFrame::create(Named("doublons") = dbl));
}



