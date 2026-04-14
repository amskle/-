from flask import Flask, request, jsonify, render_template_string
import pymysql
from werkzeug.security import generate_password_hash, check_password_hash

app = Flask(__name__)

# ==========================================
# 1. 数据库连接配置
# ==========================================
def get_db_connection():
    return pymysql.connect(
        host='127.0.0.1',
        port=3306,
        user='root',
        password='327510',  # <--- 修改为你刚刚重置的密码
        database='user_system',
        cursorclass=pymysql.cursors.DictCursor
    )

# ==========================================
# 2. 前端页面 (HTML + JavaScript)
# 为了演示方便，直接写在后端代码里
# ==========================================
HTML_PAGE = """
<!DOCTYPE html>
<html>
<head><title>用户管理系统 (CRUD)</title></head>
<body style="font-family: Arial; padding: 20px;">
    <h2>1. 注册 (增)</h2>
    <input id="regUser" placeholder="用户名">
    <input id="regPass" type="password" placeholder="密码">
    <button onclick="register()">注册</button>

    <h2>2. 登录 (查)</h2>
    <input id="logUser" placeholder="用户名">
    <input id="logPass" type="password" placeholder="密码">
    <button onclick="login()">登录</button>

    <h2>3. 修改密码 (改)</h2>
    <input id="updUser" placeholder="用户名">
    <input id="updNewPass" type="password" placeholder="新密码">
    <button onclick="update()">修改</button>

    <h2>4. 注销账号 (删)</h2>
    <input id="delUser" placeholder="用户名">
    <button onclick="deleteUser()">删除账号</button>

    <script>
        async function sendRequest(url, data) {
            const res = await fetch(url, {
                method: 'POST',
                headers: {'Content-Type': 'application/json'},
                body: JSON.stringify(data)
            });
            const result = await res.json();
            alert(result.message);
        }

        function register() {
            sendRequest('/api/register', {
                username: document.getElementById('regUser').value,
                password: document.getElementById('regPass').value
            });
        }

        function login() {
            sendRequest('/api/login', {
                username: document.getElementById('logUser').value,
                password: document.getElementById('logPass').value
            });
        }

        function update() {
            sendRequest('/api/update', {
                username: document.getElementById('updUser').value,
                new_password: document.getElementById('updNewPass').value
            });
        }

        function deleteUser() {
            sendRequest('/api/delete', {
                username: document.getElementById('delUser').value
            });
        }
    </script>
</body>
</html>
"""

# ==========================================
# 3. 后端接口 (CRUD 逻辑)
# ==========================================

# 渲染前端页面
@app.route('/')
def index():
    return render_template_string(HTML_PAGE)

# 增：注册
@app.route('/api/register', methods=['POST'])
def register():
    data = request.json
    username = data.get('username')
    password = data.get('password')
    
    # 密码加密
    hashed_pwd = generate_password_hash(password)
    
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            sql = "INSERT INTO users (username, password_hash) VALUES (%s, %s)"
            cursor.execute(sql, (username, hashed_pwd))
        conn.commit()
        return jsonify({"status": "success", "message": "注册成功！"})
    except pymysql.err.IntegrityError:
        return jsonify({"status": "error", "message": "用户名已存在！"})
    finally:
        conn.close()

# 查：登录
@app.route('/api/login', methods=['POST'])
def login():
    data = request.json
    username = data.get('username')
    password = data.get('password')
    
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            sql = "SELECT * FROM users WHERE username = %s"
            cursor.execute(sql, (username,))
            user = cursor.fetchone()
            
            if user and check_password_hash(user['password_hash'], password):
                return jsonify({"status": "success", "message": f"欢迎回来，{username}！登录成功。"})
            else:
                return jsonify({"status": "error", "message": "用户名或密码错误！"})
    finally:
        conn.close()

# 改：修改密码
@app.route('/api/update', methods=['POST'])
def update_password():
    data = request.json
    username = data.get('username')
    new_password = data.get('new_password')
    
    hashed_pwd = generate_password_hash(new_password)
    
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            sql = "UPDATE users SET password_hash = %s WHERE username = %s"
            cursor.execute(sql, (hashed_pwd, username))
            if cursor.rowcount > 0:
                conn.commit()
                return jsonify({"status": "success", "message": "密码修改成功！"})
            else:
                return jsonify({"status": "error", "message": "用户不存在！"})
    finally:
        conn.close()

# 删：注销账号
@app.route('/api/delete', methods=['POST'])
def delete_user():
    data = request.json
    username = data.get('username')
    
    conn = get_db_connection()
    try:
        with conn.cursor() as cursor:
            sql = "DELETE FROM users WHERE username = %s"
            cursor.execute(sql, (username,))
            if cursor.rowcount > 0:
                conn.commit()
                return jsonify({"status": "success", "message": "账号已注销（删除成功）！"})
            else:
                return jsonify({"status": "error", "message": "用户不存在！"})
    finally:
        conn.close()

if __name__ == '__main__':
    # 启动服务器
    app.run(debug=True, port=5000)