PULLV ans = MP(ullINF, vector<int>());

    ll totalComb = 1<<(n-1);
    for(int i = 0; i<totalComb; i++){
        bool ok = true;

        vector<bool> used(n+1, false);
        used[s] = true;

        ull sum = 0;
        vector<PII> turns;
        for(int j = 0; j<n-1; j++){
            if(i & (1<<j)){
                sum += opsCost[j].first;
                
                if(turns.size() > 0){
                    if(turns.back().first == 1){
                        turns.back().second++;
                    }else{
                        turns.PB(MP(1,1));
                    }
                }else{
                    turns.PB(MP(1,1));
                }
            }else{
                sum += opsCost[j].second;

                if(turns.size() > 0){
                    if(turns.back().first == 0){
                        turns.back().second++;
                    }else{
                        turns.PB(MP(0,1));
                    }
                }else{
                    turns.PB(MP(0,1));
                }
            }
        }
        vector<int> vec = {s};

        for(int o = 0; o<turns.size(); o++){
            int v = vec.back();
            vector<int> temp;
            int ind = 0;

            if(turns[o].first == 0){
                for(int j = 1; j<=n; j++){
                    if(ind == turns[o].second){
                        break;
                    }
                    if(j == v){
                        ok = false;
                        break;
                    }
                    if(!used[j]){
                        used[j] = true;
                        temp.PB(j);
                        ind++;
                    }
                }
            }else{
                for(int j = n; j>=1; j--){
                    if(ind == turns[o].second){
                        break;
                    }
                    if(j == v){
                        ok = false;
                        break;
                    }
                    if(!used[j]){
                        used[j] = true;
                        temp.PB(j);
                        ind++;
                    }
                }
            }

            if(!ok) break;
            for(int j = temp.size()-1; j>=0; j--){
                vec.PB(temp[j]);
            }
        }

        if(!ok){
            continue;
        }

        if(sum < ans.first){
            ans.first = sum;
            ans.second = vec;
        }
    }

    return ans;