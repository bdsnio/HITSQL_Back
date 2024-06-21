document.getElementById('LoginForm').addEventListener('submit', function(event) {
    event.preventDefault(); // 阻止表单的默认提交行为

    // 假设用户名输入字段的id为"username"
    var username = document.getElementById('username').value;
    // 存储用户名到localStorage
    localStorage.setItem('username', username); 
    // 获取密码输入的值
    var password = document.getElementById('password').value;

    // 检查密码是否正确
    if (password === "123") {

        // 如果正确，跳转到home.html
        window.location.href = 'home.html';
    } else {
        // 如果不正确，警告用户并阻止表单提交
        alert('密码错误，请重新输入！');
        // 聚焦到密码输入框，方便用户直接修改
        document.getElementById('password').focus();
    }
});