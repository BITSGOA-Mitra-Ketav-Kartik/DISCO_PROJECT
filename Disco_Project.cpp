#include <iostream>
#include <bits/stdc++.h>
using namespace std;
map<string, vector<string>> allot;
map<string, double> profx;
vector<pair<string, vector<string>>> remCDC;
vector<pair<map<string, vector<string>>, map<string, double>>> diffAllot;
/*vector of pairs of maps where first map has allocations after CDCs
 allotmnent and thesecond map has the number of courses that 
 a particular prof can still offer after 
 this.*/ 
set<map<string, vector<string>>> final;/* set  of all possible 
allotments which eliminates duplicate allotments*/
map<string, vector<string>> pte;
/*map from professors to vector of string where vector stores all 
electives */
vector<pair<string, vector<string>>> remEle;/*remainig electives to be 
alloted*/
int n;
int total = 0;
int finaltotal = 0;
int crash = 0;
bool canAssignEle1(string prof, int mlvl)
{
  if ((diffAllot[mlvl].second)[prof] >= 1)
  {
    return true;
  }
  return false;
}
bool canAssignEle2(string prof, int mlvl)
{
  if ((diffAllot[mlvl].second)[prof] >= 0.5)
  {
    return true;
  }
  return false;
}
bool canAssign1(string prof)
{
  if (profx[prof] >= 1)
  {
    return true;
  }
  return false;
}
bool canAssign2(string prof)
{
  if (profx[prof] >= 0.5)
  {
    return true;
  }
  return false;
}
bool done(int mlvl)
{
  bool flag = true;
  for (auto i : diffAllot[mlvl].second)
  {
    if (i.second)
    {
      return false;
    }
  }
  return flag;
}
void assignEle(int mlvl, int level)
{
  if (done(mlvl))
  {
    finaltotal++;
    map<string, vector<string>> m;
    m = diffAllot[mlvl].first;
    final.insert(m);
    return;
  }
  else if (level == remEle.size())
  {
    return;
  }
  for (auto i : remEle[level].second)
  {
    if (canAssignEle1(i, mlvl))
    {
      (diffAllot[mlvl].second)[i]--;
      vector<string> v;
      v.push_back(i);
      diffAllot[mlvl].first[remEle[level].first] = v;
      assignEle(mlvl, level + 1);
      (diffAllot[mlvl].second)[i]++;
      (diffAllot[mlvl].first).erase(remEle[level].first);
    }
  }
  for (auto i : remEle[level].second)
  {
    if (canAssignEle2(i, mlvl))
    {
      (diffAllot[mlvl].second)[i] -= 0.5;
      for (auto j : remEle[level].second)
      {
        if (canAssignEle2(j, mlvl) && i != j)
        {
          vector<string> v;
          v.push_back(i);
          v.push_back(j);
          sort(v.begin(),v.end());
          (diffAllot[mlvl].second)[j] -= 0.5;
          diffAllot[mlvl].first[remEle[level].first] = v;
          assignEle(mlvl, level + 1);
          (diffAllot[mlvl].second)[j] += 0.5;
        }
      }
      (diffAllot[mlvl].second)[i] += 0.5;
      (diffAllot[mlvl].first).erase(remEle[level].first);
    }
  }
  assignEle(mlvl, level + 1);
  return;
}
void assignCDC(int level)
{
  if (level == n)
  {
    total++;
    map<string, vector<string>> m;
    m = allot;
    map<string, double> m1;
    m1 = profx;
    for (auto i : profx)
    {
      if (i.second == 0)
      {
        m1.erase(i.first);
      }
    }
    diffAllot.push_back({m, m1});
    return;
  }
  for (auto i : remCDC[level].second)
  {
    if (canAssign1(i))
    {
      profx[i]--;
      vector<string> v;
      v.push_back(i);

      allot[remCDC[level].first] = v;
      assignCDC(level + 1);
      profx[i]++;
      allot.erase(remCDC[level].first);
    }
  }
  for (auto i : remCDC[level].second)
  {
    if (canAssign2(i))
    {
      profx[i] = profx[i] - 0.5;
      vector<string> v;
      v.push_back(i);
      for (auto j : remCDC[level].second)
      {
        if (canAssign2(j) && i != j)
        {
          vector<string> v;
          v.push_back(i);
          v.push_back(j);
          sort(v.begin(),v.end());
          allot[remCDC[level].first] = v;
          profx[j] = profx[j] - 0.5;
          assignCDC(level + 1);
          profx[j] = profx[j] + 0.5;
          allot.erase(remCDC[level].first);
        }
      }
      profx[i] = profx[i] + 0.5;
    }
  }
  return;
}
int main()
{
#ifndef ONLINE_JUDGE
  freopen("input3.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#else
#endif
  string s;
  int flag = 1;
  string str;
  map<string, vector<vector<string>>> input;
  while (flag)
  {
    vector<vector<string>> v;
    for (int i = 0; i < 6; i++)
    {

      cin >> s;
      if (i == 0)
      {
        str = s;
      }
      else if (i == 1)
      {
        vector<string> v1;
        v1.push_back(s);
        v.push_back(v1);
      }
      else
      {
        vector<string> v2;
        if (s == "-")
        {
          v2.push_back(s);
          v.push_back(v2);
        }
        else
        {
          vector<int> comma;
          for (int i = 0; i < s.size(); i++)
          {
            if (s[i] == ',')
            {
              comma.push_back(i);
            }
          }
          if (comma.size() != 0)
          {
            string s1 = s.substr(0, 6);
            v2.push_back(s1);
            for (int i = 0; i < comma.size(); i++)
            {
              string s1 = s.substr(comma[i] + 1, 6);
              v2.push_back(s1);
            }
          }
          else
          {
            v2.push_back(s);
          }
          v.push_back(v2);
        }
        input[str] = v;
      }
      if (s == "END")
      {
        flag = 0;
        break;
      }
    }
  }
  map<string, vector<string>> ctp;//ctp==course to professor
  for (const auto &i : input)
  {

    for (const auto &innerVec : i.second)
    {
      for (const auto &str : innerVec)
      {
        if (str == "-" || str == "1.5" || str == "0.5" || str == "1")
        {
          if (str != "-")
          {
            profx[i.first] = stod(str);
          }
        }
        else
        {
          if (ctp.count(str) > 0)
          {
            vector<string> v = ctp[str];
            v.push_back(i.first);
            ctp[str] = v;
          }
          else
          {
            vector<string> v;
            v.push_back(i.first);
            ctp[str] = v;
          }
        }
      }
    }
  }

  map<string, vector<string>> cdc;/* cdc is map from each cdc to 
  vector of profs offering that particular cdc*/
  for (auto i : ctp)
  {
    string s = (i.first).substr(0, 5);
    if ((s == "ugcdc" || s == "hdcdc"))
    {
      cdc[i.first] = i.second;
    }
    else
    {
      remEle.push_back({i.first, i.second});
    }
  }
  int flag1 = 1;
  int count;
  int eleTotal = ctp.size() - cdc.size();
  while (flag1)
  {
    count = 0;
    for (auto j : cdc)
    {
      double sum = 0;
      int x1 = 0, x2 = 0, x3 = 0;
      for (auto str : j.second)
      {
        sum = sum + profx[str];
        if (profx[str] == 1.5)
        {
          x1++;
        }
        else if (profx[str] == 1)
        {
          x2++;
        }
        else
        {
          x3++;
        }
      }

      if (sum == 0.5 && allot.count(j.first) == 0)
      {
        crash=1;
        break;
      
      }
      else if (sum == 1)
      {
        if (x2 == 1)
        {
          for (auto str : j.second)
          {
            if (profx[str] == 1)
            {
              vector<string> p;
              p.push_back(str);
              profx[str] = 0;
              allot[j.first] = p;
            }
          }
        }
        else
        {
          vector<string> p;
          for (auto str : j.second)
          {

            if (profx[str] == 0.5)
            {
              profx[str] = 0;
              p.push_back(str);
            }
          }
          allot[j.first] = p;
        }
        count++;
      }

      else if (sum == 1.5)
      {
        if (x3 == 1)
        {
          for (auto str : j.second)
          {
            if (profx[str] == 1.5)
            {
              vector<string> p;
              p.push_back(str);
              profx[str]--;
              allot[j.first] = p;
            }
          }
          count++;
        }
      }
    }

    for (auto i : allot)
    {
      cdc.erase(i.first);
    }

    if (!count)
    {
      break;
    }
  }
  for (auto i : input)
  {
    vector<string> v;
    for (auto j : i.second)
    {
      for (auto k : j)
      {
        string s = k.substr(0, 5);
        if (s == "ugele" || s == "hdele")
        {
          v.push_back(k);
        }
      }
    }
    if (profx[i.first])
    {
      pte[i.first] = v;
    }
  }
  for (auto i : cdc)
  {
    remCDC.push_back(make_pair(i.first, i.second));
  }

  n = remCDC.size();
  assignCDC(0);
  sort(diffAllot.begin(),diffAllot.end());
  auto itr1=unique(diffAllot.begin(),diffAllot.end());
  diffAllot.erase(itr1,diffAllot.end());
  map<string, double> elective;
  for (auto i : ctp)
  {
    string s = (i.first).substr(0, 5);
    if ((s == "ugele" || s == "hdele"))
    {
      elective[i.first] = 0;
    }
  }
  int a[diffAllot.size()] = {};
   cout << diffAllot.size();
   cout<<" "<<"POSSIBLE ALLOTMENTS AFTER ALLOTING CDCS" << endl;
  for (int i = 0; i < diffAllot.size(); i++)
  {
    double left = 0;
    for (auto j : diffAllot[i].second)
    {
      left += j.second;
      if (j.second > 0 && (pte[j.first]).size() == 0)
      {
        a[i] = -1;
        break;
      }
      if (j.second == 1.5 && (pte[j.first]).size() < 2)
      {
        a[i] = -1;
        break;
      }
    }
    if (left > eleTotal)
    {
      a[i] = -1;
    }
  }

  int size = diffAllot.size();
  auto itr = diffAllot.begin();
  int del = 0;
  for (int i = 0; i < size; i++)
  {
    if (a[i] == -1)
    {
      diffAllot.erase(itr + i - del);
      del++;
    }
  }
  
  int b[diffAllot.size()] = {};

  size = diffAllot.size();
  itr = diffAllot.begin();
  del = 0;
  for (int i = 0; i < size; i++)
  {
    if (b[i] == -1)
    {
      diffAllot.erase(itr + i - del);
      del++;
    }
  }
  if (!diffAllot.size())
  {
    crash = 1;
    cout<<"NO POSSIBLE COMBINATIONS";
    return 0;
  }
   cout << diffAllot.size()<<" ";
   cout<<"POSSIBLE COMBINATIONS AFTER CHECKING PROFESSORS WORK LOAD CONSTRAINTS" ;
   cout<< endl;
  for (int i = 0; i < diffAllot.size(); i++)
  {
    assignEle(i, 0);
  }
  cout << final.size()<<" ";
  cout<<"FINAL COMBINATIONS AFTER ALLOTING ELECTIVES AND SATISFYING WORK LOAD CONSTRAINTS" << endl;
  if (!final.size())
  {
    crash = 1;
    cout<<"NO POSSIBLE COMBINATIONS";
    return 0;
  }
  if (crash == 0)
  {
    for (auto i:final)
    {
      for (auto j : i)
      {
        cout << j.first << " ";
        for (auto k : j.second)
        {
          cout << k << " ";
        }
        cout << endl;
      }
      cout << endl;
    }
  }
  cout<<"- - - - - -THE END- - - - - -";
  return 0;
}