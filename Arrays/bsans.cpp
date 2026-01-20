#include <iostream>
#include <climits>
#include <vector>
#include <algorithm>//max_element
#include <cstdlib>
#include <cmath>//ceil


int find_root_byBS(int n = 36){
    int l =0,r = n/2,m,ans;
    while(l<=r){
        m = (l+r)/2;
        if(m*m<=n){
            ans = m;
            l=m+1;
        }else{
            r = m-1;
        }
    }
    return ans;
}

int check_root(int n =4,int m=69){
    int low = 1,high = m , mid;
    while(low<=high){
        mid = (low + high)/2;
        int ans = mid;
        for(int _=1 ; _<n;_++){
            ans *=mid;
        }
        if(ans==m)return mid;
        else if(ans <m)low = mid +1;
        else high=mid-1;
    }
    return -1;
}

int koko_prob(std::vector<int> piles = {873375536,395271806,617254718,970525912,634754347,824202576,694181619,20191396,886462834,442389139,572655464,438946009,791566709,776244944,694340852,419438893,784015530,588954527,282060288,269101141,499386849,846936808,92389214,385055341,56742915,803341674,837907634,728867715,20958651,167651719,345626668,701905050,932332403,572486583,603363649,967330688,484233747,859566856,446838995,375409782,220949961,72860128,998899684,615754807,383344277,36322529,154308670,335291837,927055440,28020467,558059248,999492426,991026255,30205761,884639109,61689648,742973721,395173120,38459914,705636911,30019578,968014413,126489328,738983100,793184186,871576545,768870427,955396670,328003949,786890382,450361695,994581348,158169007,309034664,388541713,142633427,390169457,161995664,906356894,379954831,448138536} ,const  int total_hours = 943223529){

    long long low = 1 ,speed , hour_needed;
    
    // still O[n] returns ptr hence derefrencing it 
    long long high = *std::max_element(piles.begin(),piles.end());

    //gives reference to the local function hence can use local var
    auto needed_hrs = [&](const long long hourly) {
        long long hour_passed =0;
        for(const int &pile :piles){
            hour_passed += (pile + hourly - 1) / hourly;
        }
        return hour_passed;
    };

    while(low<=high){
        speed = (low+high)/2;
        hour_needed = needed_hrs(speed);
        if(hour_needed <=total_hours)high=speed-1;
        else low = speed+1;
    }
    //never -1 gonna happen but still 
    return static_cast<int>(low);
}

int main(){
    auto res = koko_prob();
    std::cout<<res<<std::endl;
    return 0;
}
