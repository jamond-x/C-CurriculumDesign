```c++
 //  string ??�� CString!!
string user;
cin >> user;
CString theuser(user.c_str());    
```

```c++\
// CString Format �����������?����ˡ & CString ??�� string!!
CString str = "";
CString one = "2565";
CString two = "WHERE Name = '��??'";
CString three = "66660";
str.Format(_T("SELECT * FROM %s %s %s"),one,two,three);
string save(CW2A(str.GetString()));   
```

```c++
// �� _variant_t ??? string  !
long num = 1;
_variant_t one(num);
string msg = "";
msg = (char*)(_bstr_t)one; 
```

```c++
//  string ??��  const char* 
string sql = "SELECT * FROM ";
string sql2 = "Employees";
sql += sql2;
const char* sqlstr = sql.c_str();
```

