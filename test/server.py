from flask import Flask, request, jsonify, send_from_directory
import os

app = Flask(__name__)

# 配置参数
UPLOAD_FOLDER = 'files'  # 上传文件保存目录
TOKEN = 'wqei9dh43uburgr'  # 安全令牌
UP_TOKEN = '9bji32r834tfgw'
ALLOWED_EXTENSIONS = {'txt', 'pdf', 'png', 'jpg', 'jpeg', 'gif', 'doc', 'docx'}  # 允许的文件类型
MAX_CONTENT_LENGTH = 16 * 1024 * 1024  # 最大文件大小 (16MB)

# 确保上传目录存在
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

# 检查文件扩展名
def allowed_file(filename):
    if '.' not in filename:
        return False
    ext = filename.rsplit('.', 1)[1].lower()
    return ext in ALLOWED_EXTENSIONS

# 验证 Token
def validate_token():
    token = request.args.get('token') or request.headers.get('Authorization')
    return token == TOKEN

def validate_up_token():
    token = request.args.get('token') or request.headers.get('Authorization')
    return token == UP_TOKEN

@app.route('/upload', methods=['POST'])
def upload_file():
    # 验证 Token
    if not validate_up_token():
        return "无效的访问令牌", 401
    
    # 检查文件是否存在
    if 'file' not in request.files:
        return "请选择文件", 400
    
    file = request.files['file']
    
    # 检查文件名是否为空
    if file.filename == '':
        return "文件名不能为空", 400
    
    # 验证文件类型
    if file and allowed_file(file.filename):
        # 保存文件
        filename = file.filename
        file.save(os.path.join(UPLOAD_FOLDER, filename))
        return f"文件上传成功: {filename}", 200
    else:
        return f"不允许的文件类型，允许类型: {', '.join(ALLOWED_EXTENSIONS)}", 400

@app.route('/download/<filename>')
def download_file(filename):
    # 验证 Token
    if not validate_token():
        return "无效的访问令牌", 401
    
    return send_from_directory(UPLOAD_FOLDER, filename, as_attachment=True)

@app.route('/list')
def file_list():
    # 验证Token
    if not validate_token():
        return "无效的访问令牌", 401
    
    # 获取文件列表
    try:
        files = os.listdir(UPLOAD_FOLDER)
    except FileNotFoundError:
        files = []
    
    # 返回纯文本文件列表
    response = "\n".join(files) if files else "没有找到文件"
    return response, 200, {'Content-Type': 'text/plain'}

@app.route('/')
def index():
    return """
    文件上传服务器 - 核心功能
    ------------------------
    /upload (POST) - 上传文件 (需提供 token)
    /download/<filename> (GET) - 下载文件 (需提供 token)
    /list (GET) - 查看文件列表 (需提供 token)
    """

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=6000, debug=True)