# OTA 中服务端与硬件交互接口 #
## 1.设备上报IMEI，固件版本，硬件版本 ##
### 设备上报IMEI数据包格式
### 设备每次开始更新时上报一次该数据包
设备山上报数据报文|
---|
{<br>&emsp;"imei" : "863703030562",<br>&emsp;"hardware_version" : "0101",<br>&emsp;"software_version" : "0102"<br>}|
