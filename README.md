# 网会sdk接入指南

[SDK集成](#importSdk)<br>
[接口方法](#sdkapi)<br>
[标准流程](#standard)<br>

```
未完成:
问题:
```
## <span id = "importSdk">1 SDK集成</span>

下载WHConfclient.a文件拖到项目中
在工程中引入头文件 ```#import<###/WHConfClientSDK.h> ```


##  <span id = "sdkapi">2 接口方法 </span>

### 2.1 实例化相关
```
/**
* 初始化创建WHConfClient实例
**/
- (instancetype _Nonnull )instanceWithDelegate:(nonnull id<WHConfClientDelegate>)confClientDelegate;

/**
* 释放WHConfClient内部资源
**/
- (int)release;

```

### 2.2 服务器相关
```
/**
* 连接服务，帐号密码登录
* userName - 用户名
* password - 密码
* nickName - 昵称（可以为空）
* serverIPS - 服务器ip等信息（1:192.168.0.100:6501:6501 描述：服务器ID:IP:udp端口:tcp端口）, 有多台服务器可以连接填写多个
**/
- (int)connect:(NSString * _Nullable)userName
password:(NSString * _Nullable)pwd
nickName:(NSString * _Nullable)nickName
serverIPS:(NSArray * _Nullable)serverIPS;

/**
* 连接服务，验证码登录
* code - 验证码
* nickName - 昵称（可以为空）
* serverIPS - 服务器ip等信息（1:192.168.0.100:6501:6501 描述：服务器ID:IP:udp端口:tcp端口）, 有多台服务器可以连接填写多个
**/
- (int)connect:(unsigned int)code
nickName:(NSString * _Nullable)nickName
serverIPS:(NSArray * _Nullable)serverIPS;

/**
* 断开服务
**/
- (void)disconnect;
```

### 2.3 会议室相关
```
/**
* 进入会议室
* roomID - 会议室ID
* roomPwd - 会议室密码;
**/
- (int)joinRoom:(int)roomID 
roomPwd:(NSString * _Nullable)roomPwd;

/**
* 取消入会等待
**/
- (int)cancelWaiting;

/**
* 退出会议室
**/
- (int)quitRoom;

/**
* 获取本机用户当前进入的会议室信息
**/
- (ACWHRoomAttr * _Nullable)getRoomattr;

/**
* 向服务器请求获取会议室列表
**/
- (int)getRoomattrList;

/**
* 修改会议模式
* nRoomType = 0 : 自由讨论
* nRoomType = 1 : 集中管理
**/
- (int)setRoomType:(int)nRoomType;

/**
* 获取本机用户id
**/
- (u_int64_t)getLocalUserID;

/**
* 获取本机用户用户名
**/
- (NSString * _Nullable)getUserName;

/**
* 获取本机用户密码
**/
- (NSString * _Nullable)getUserPwd;

/**
* 获取本机用户昵称
**/
- (NSString * _Nullable)getFriendName;

/**
* 获取会议室里的用户列表
**/
- (NSArray * _Nullable)getAllAttender;

/**
* 获取会议室里的用户数量
**/
- (int)getAttenderCount;

/**
* 获取会议室里的指定用户信息
**/
- (ACWHAttendee * _Nullable)getAttenderByID:(u_int64_t)userID;

/**
* 获取本机用户有没有数据同步操作权限
**/
- (BOOL)getOperaDataSync;

/**
* 修改昵称 密码
* pszUsername - 用户名
* pszFriendname - 昵称
* pszPasswd - 密码
**/
- (int)updateUserInfo:(uint64_t)dstID
andUsername:(NSString *_Nullable)pszUsername
andPszFriendname:(NSString *_Nullable)pszFriendname
andPszPasswd:(NSString *_Nullable)pszPasswd;

/**
* 中继协议 比如管理员远程操作其他人
* ulUserstatus-参考 “WHUserStatus.h"
**/
- (int)updateUserstatus:(u_int)ulUserstatus 
value:(int)nValue;

/**
* 远程上麦
* relayProtoId - 参考附表3
* arrID - 一个或多个账户
**/
-(int)remoteMakeSpeaker:(u_short)relayProtoId 
buflen:(int)len arrUsrID:(NSArray *_Nullable)arrID;

/**
* 服务器获取video信息
* relayProtoId - 参考附表3
**/
-(int)remoteGetAVInfo:(u_short)relayProtoId
buf:(unsigned char *_Nullable)buf
len:(int)len
arrUsrID:(NSArray *_Nullable)arrID;
/**
* 用户是否具备权限
* userID - 查询的用户id
* sTypePriv - 参考附表2
**/
-(BOOL)allowUserOperPrivsEx:(uint64_t)userID 
PrivName:(NSString *_Nullable)sTypePriv;

/**
* 密码申请临时管理员
**/
- (int)applyTemporaryAdmin:(NSString * _Nonnull)pszPasswd;

/**
* 对等待的用户操作 
* bAgree: true- 同意; false- 不同意; 
* pid- 一个或多个账户 
* nCount:账号数量
**/
- (int)operWaitingUser:(BOOL)bAgree
and:(ID_TYPE *_Nullable)pId
and:(int)nCount;

/**
* 点名
**/
- (void)rollCallRsp;
```

### 2.4 音频相关
```
/**
* 开启语音设备
**/
- (int)startAudio;

/**
* 关闭语音设备
**/
- (int)closeAudio;

/**
* 上麦
* opID-操作者id 
* speakerID-上麦者id
**/
- (int)tryMakeASpeaker:(uint64_t)opID 
speakerID:(uint64_t)speakerID;

/**
* 下麦
**/
- (int)cancelSpeaker:(uint64_t)speakerID;

/**
* 获取语音标记
* type 参照 WHAVType-enum AudioType
* 返回值 1 - 禁止，0 - 打开
**/
- (int)getAudioinfo:(int)type;

/**
* 设置语音标记
* type 参照 WHAVType-enum AudioType
* type = audiotypeVolInIsMute
* curval = 1 表示麦克风打开
* curval = 0 表示麦克风禁止
**/
-(int)setAudioinfo:(int)type 
value:(int)curval;

/**
* 设置扬声器外放
* bspeaker = true - 使用扬声器; false - 使用听筒
**/
- (int)setOverrideSpeaker:(BOOL)bSpeaker;

/**
* 获取扬声器外放标记
**/
- (BOOL)getOverrideSpeaker;

/**
* 获取麦克风名字
**/
- (NSString * _Nonnull)getReadCardName;

/**
* 获取扬声器名字
**/
- (NSString * _Nonnull)getPlayCardName;

```

### 2.5 视频相关
```
/**
* 启动摄像头
* videoSize - 参考“WHVideoSize.h"
* fps - 帧率
* bfront - YES 前摄像头，NO 后摄像头
**/
- (int)startCamera:(int)videoSize 
fps:(int)fps 
isFront:(BOOL)bfront;

/**
* 关闭摄像头
**/
- (int)stopCamera;

/**
* 切换前后摄像头
* bfront - YES 前摄像头，NO 后摄像头
**/
- (int)switchCamera:(BOOL)bfront;

/**
* 切换摄像头参数
* videoSize - 参考“WHVideoSize.h"
* fps - 帧率
**/
- (int)changeCameraFormat:(int)videoSize 
fps:(int)fps;

/**
* 获取本机用户视频状态标记
* index - 第几路视频。当前只表示全部所以值为0xff
* 返回值 0 - 禁止 ； 1 - 打开
**/
- (int)getVideoStatus:(u_char)index;

/**
* 设置视频状态
* index - -1
* nStatus : 1 - 开启视频; 0 - 关闭视频
**/
- (int)setVideoStatus:(u_char)index 
videoStatus:(int)nStatus;

/**
* 观看视频
* userID - 用户ID
* ucIndex - 用户第几路视频
**/
- (int)queryVideo:(uint64_t)userID 
videoIndex:(u_char)ucIndex;

/**
* 停止观看视频
* userID - 用户ID
* ucIndex - 用户第几路视频
**/
- (int)releaseVideo:(uint64_t)userID 
videoIndex:(u_char)ucIndex;

/**
* 添加视频绘制
* userID - 用户id
* index - 用户视频索引 从0开始编号 0 - 摄像头 ; 15 - 影音
* adapter - 数据缓存
**/
- (int)addVideoDataAdapter:(u_int64_t)userID 
videoIndex:(u_char)index 
videoDataAdapter:(WHDataAdapter *)adapter;

/**
* 移除视频绘制
* userid - 用户id
* index - 用户视频索引 从0开始编号 0 - 摄像头 ;15 - 影音;
**/
- (int)removeVideoDrawAdapter:(u_int64_t)userID 
videoIndex:(u_char)index;

/**
* 获取显卡名
**/
- (NSString * _Nonnull)getGraphicsName;

/**
* 停止绘制所有视频
**/
- (void)pauseDrawAllVideo;

/**
* 停止绘制一路视频
* userid - 停止用户的id
**/
- (void)pauseDrawVieoWith:(u_int64_t)userid;

/**
* 恢复绘制所有视频
**/
- (void)resumeDrawAllVideo;

/**
* 恢复绘制一路视频
* userid - 恢复用户的id
**/
- (void)resumeDrawVideoWit:(u_int64_t)userid;
```

### 2.6 屏幕共享相关
```
/**
* 获取当前会议室正在屏幕共享的用户id
**/
- (u_int64_t)getScreenShareID;

/**
* 是否有用户在屏幕共享
**/
- (BOOL)getScreenShareState;

/**
* 管理员开启或停止用户的屏幕共享
**/
- (int)grantScreenShare:(u_short)relayProtoId 
toId:(uint64_t)toId 
andbGrant:(BOOL)bGrant;

/**
* 请求开始屏幕共享
**/
- (int)tryMakeAScrsharer:(uint64_t)myid;

/**
* 请求取消屏幕共享
* myId - 用户id
* reason - 结束共享原因(例如程序停止,扩展停止等)
* cancelScreenShare 
**/
- (int)cancelScrsharer:(uint64_t)myid
with:(NSString *_Nullable)reason
and:(cancelScrShare _Nullable )cancelScreenShare;

/**
* 修改屏幕共享采集分辨率
**/
- (void)setScreenShareResolution:(int)resolution;

/**
* 设置屏幕共享绘制
**/
- (int)setScreenShareDraw:(u_int64_t)userID 
dataAdapter:(WHDataAdapter *)adapter;

/**
* 停止屏幕共享绘制
**/
- (int)resetScreenShareDraw:(u_int64_t)userID;

/**
* 停止绘制所有视频
**/
- (void)pauseDrawAllVideo;

/**
* 停止绘制一个用户的视频
* userid - 用户id
**/
- (void)pauseDrawVieoWith:(u_int64_t)userid;

/**
* 恢复绘制所有视频
**/
- (void)resumeDrawAllVideo;

/**
* 恢复绘制一个用户的视频
* userid - 用户id
**/
- (void)resumeDrawVideoWit:(u_int64_t)userid;

```

### 2.6 其它
```
/**
* 获取服务器时间, 结果在回调获取
**/
- (int)getSrvTime;
/**
* 获取音频信道
**/
- (int)getAVAudioSessionRouteInM_conf;

/**
* 获取当前音频detaitype 0-下麦且没有影音播放 1上麦没有影音播放 2 下麦有影音播放 3 上麦有影音播放
**/
- (WHMediaAudioType)getAudioSessionDetailTypeBy:(u_int64_t)userid;
```

## 3  回调结果
```
/**
* 认证结果 用户连接服务器结果都会从这里返回
* nResulte - 执行结果 参考附表1
* connType - 连接类型 参考附表4
* connIndex - 当前connectType的连接索引
**/
- (int)onAuthenticated:(int)nResulte 
connType:(u_char)connType 
connIndex:(u_short)connIndex;

/**
* 连接  建立一条socket连接
* connType - 连接类型 参考附表4
* connIndex - 当前connectType的连接索引
**/
- (int)onConnect:(u_char)connType 
connIndex:(u_short)connIndex;

/**
* 连接断开 socket连接断开
* nResulte - 执行结果 参考附表1
* connType - 连接类型 参考附表4
* connIndex - 当前connectType的连接索引
**/
- (int)onDisconnect:(int)nResulte 
connType:(u_char)connType 
connIndex:(u_short)connIndex;

/**
* 获得会议室属性列表 
* nResulte - 执行结果 参考附表1
* arrRoomAttr - 会议室属性参照"ACWHRoomAttr.h"
**/
- (int)onGetRoomAttrSimpleList:(int)nResulte 
roomAttrs:(NSArray *_Nullable)arrRoomAttr;

/**
* 进入会议室 
* nResulte - 执行结果 参考附表1
* roomID - 会议室ID ; 
* userID - 用户ID ; 
* nickName - 昵称
**/
- (int)onJoinConfroom:(int)nResulte 
roomID:(ROOMID_TYPE)roomID 
userID:(u_int64_t)userID 
nickName:(NSString *_Nullable)nickName;

/**
* 取消等待 (会议室锁定情况 不是管理员用户 需要等待管理员允许再进入会议室)
* nResulte - 执行结果 参考附表1
* roomID - 会议室id
* userID - 用户id
* uniqueID - sdk产生的随机id
**/
- (int)onCancelWaiting:(int)nResulte 
roomID:(ROOMID_TYPE)roomID 
userID:(u_int64_t)userID 
uniqueID:(u_int64_t)uniqueID;

/**
* 添加用户 用户属性参考 "ACWHAttendee.h"
**/
- (int)onAddAttender:(ACWHAttendee * _Nonnull)acAttendee;

/**
* 添加多个用户  用户属性参考 "ACWHAttendee.h"
**/
- (int)onAttenderlist:(NSArray * _Nonnull)attendeList;

/**
* 更新用户  用户属性参考 "ACWHAttendee.h"
**/
- (int)onUpdateAttender:(ACWHAttendee * _Nonnull)acAttendee;

/**
* 离开会议室 
* result - 执行结果 参考附表1
* userID - 离开会议室的用户ID
**/
- (int)onLeaveConfroom:(uint64_t)userID 
result:(int)result;

/**
* 更新用户状态  
* nResult - 执行结果 参考附表1
* opID - 操作的用户ID 
* userStatus - 用户状态 参考 “WHUserStatus.h"
* nValue - 更新值
**/
- (int)onUpdateUserstatus:(int)nResult 
operatorID:(uint64_t)opID 
userStatus:(u_int)userStatus 
value:(int)nValue;

/**
* 下麦 
* nResult-执行结果 参考附表1
* opID - 操作的用户ID 
* speakerID - 下麦者ID
**/
- (int)onCancelspeaker:(int)nResult 
operatorID:(uint64_t)opID 
speakerID:(uint64_t)speakerID;

/**
* 上麦 
* nResult - 执行结果 参考附表1 
* opID - 操作的用户ID 
* speakerID - 上麦者ID
**/
- (int)onTryMakeaspeaker:(int)nResult 
operatorID:(uint64_t)opID 
speakerID:(uint64_t)speakerID;

/**
* 影音播放 
* nResult - 执行结果 参考附表1
* opID - 操作的用户ID 
* playMediaUserID - 影音播放者ID
**/
- (int)onTryPlaymediafile:(int)nResult 
operatorID:(u_int64_t)opID 
playMediaUserID:(u_int64_t)playMediaUserID;

/**
* 停止影音播放 
* nResult - 执行结果 参考附表1 
* opID - 操作的用户ID 
* playMediaUserID - 影音播放者ID
**/
- (int)onStopPlaymediafile:(int)nResult 
operatorID:(uint64_t)opID 
playMediaUserID:(uint64_t)playMediaUserID;

/**
* 请求观看视频  
* nResult - 执行结果 参考附表1
* opID - 操作的用户ID 
* sessionID - 视频sessionID  它由四部分组成 企业ID+用户ID+Session类型（此处类型为视频）+Session索引（第几路视频）；具体可以查看 “whdifine.h"-#define SET_SESSIONID_EX(id, type, index)
**/
- (int)onQueryvideo:(int)nResult 
operator:(u_int64_t)opID 
videoSessionID:(uint64_t)sessionID;

/**
* 停止观看视频 
* nResult - 执行结果 参考附表1 
* opID - 操作的用户ID  
* sessionID - 视频sessionID
**/
- (int)onReleasevideoRsp:(int)nResult 
operator:(uint64_t)opID 
videoSessionID:(uint64_t)sessionID;

/**
* 更新会议室属性
* nResult - 执行结果 参考附表1   
* roomID - 会议室id
* opID - 操作的用户ID
* roomAttr - 会议室属性 参考 ACWHRoomAttr.h
**/
- (int)onUpdateRoomAttr:(u_short)usResult 
roomID:(ROOMID_TYPE)roomID 
operatorID:(u_int64_t)opID 
roomAttr:(ACWHRoomAttr *_Nonnull)roomAttr;

/**
* 更新用户权限 
* usResult - 结果  
* idUser - 更新的用户ID  
* userStatus - 更新哪个状态  
* value - 更新值
**/
- (int)onUpdateUseridentity:(u_short)usResult 
idUser:(u_int64_t)idUser 
userStatus:(u_int)userStatus 
value:(int)value;

/**
* 更新用户昵称 
* usResult - 结果  
* idUser - 更新的用户ID 
* nickName - 用户昵称
**/
- (int)onUpdateFriendName:(u_short)usResult 
idUser:(u_int64_t)idUser 
nickName:(NSString *_Nullable)nickName;

/**
* 踢出用户 
* opid - 操作的用户ID  
* iduser - 更新的用户ID 
* reason - 原因
**/
- (int)onKickoutHandler:(u_int64_t)opid 
idUser:(u_int64_t)idUser 
reason:(NSString *_Nullable)reason;

/**
* 设置会议室管理员 
* oper_type: 1-用户设为管理员 2-用户取消管理员  
* dstID - 设置的用户ID
* bGrant : true - 成为管理员, bGrant - 取消管理员
**/
- (int)onUpdateRoomAdmin:(u_int)oper_type 
dstID:(u_int64_t)dstID 
grant:(BOOL)bGrant;

/**
* 授权上麦 
* opid - 操作的用户ID  
* idUser - 被操作用户ID 
**/
- (int)onGrantMakeASpeaker:(u_int64_t)opid 
idUser:(u_int64_t)idUser;

/**
* 远程控制音频 
* opid - 操作者ID  
* idUser 被操作用户ID 
* type - 参考WHAVType.h  type == audiotypeVolInIsMute-麦克风是否静音 value: 0-非静音 1-静音
**/
- (int)onSetAudioInfo:(u_int64_t)opid 
idUser:(u_int64_t)idUser 
type:(int)type 
value:(int)value;

/**
* 远程控制摄像头分辨率
* ucIndex - 第ucIndex路视频
* width - 视频宽度
* height - 视频高度
* frame - 视频帧率
**/
- (int)onSetVcapInfoUserid:(u_int64_t)userid 
ucIndex:(u_char)ucIndex 
width:(int)width 
height:(int)height 
frame:(int)frame;

/**
* 获取音视频信息并发送给服务器
**/
- (int)onGetAVInfoReq:(u_int64_t)idSrc;

/**
* 会议室锁定时 等待进入会议室的用户
* waitUserDic : key - 用户名(NSNumber) ; value - 昵称(NSString)
**/
- (int)onWaitingUserList:(NSDictionary * _Nullable)waitUserDic;

/**
* 授权临时管理员
* dstID - 被授权用户id
* ulUseridentity - 默认4(临时管理员)
* result - 执行结果
* bGrant : true - 成为管理员 ; false - 取消管理员

**/
- (int)onGrantTemporaryAdmin:(u_int64_t)dstID 
useridentity:(int)ulUseridentity 
grant:(BOOL)bGrant 
result:(u_short)result;

/**
* 音量值显示
* sid -  视频session id  它由四部分组成 企业ID+用户ID+Session类型（此处类型为视频）+Session索引（第几路视频）；具体可以查看 “whdifine.h"-#define SET_SESSIONID_EX(id, type, index)
*  iVolume - 音量值
**/
- (int)onVolumeShow:(u_int64_t)sid 
volume:(int)iVolume;

/**
* 开始屏幕共享
* nResult - 结果 参考附表1
* opid - 操作者id
* dstID - 共享平的用户id
* sharerName - 共享用户的昵称
**/
- (int)onMakeascrsharer:(int)nResult 
operateID:(u_int64_t)opid 
dstID:(u_int64_t)dstID 
sharerName:(NSString *_Nullable)sharerName;

/**
* 取消屏幕共享
* nResult - 结果 参考附表1
* opid - 操作的用户id
* dstID - 取消共享的用户id
**/
- (int)onCancelscrsharer:(int)nResult 
operateID:(u_int64_t)opid 
dstID:(u_int64_t)dstID;

/**
* 接收文字信息
* sender - 发送消息的用户id
* receiver - 接收消息的用户id
* bPrivate - 是否是悄悄话
* msgTxt - 消息内容
**/
- (int)onChatRecFrom:(u_int64_t)sender 
to:(u_int64_t)receiver 
bPrivate:(BOOL)bPrivate 
msgTxt:(NSString *_Nullable)msgTxt;

/**
* 获取服务器时间
**/
- (void)onGetServerTime:(long)serverTime;

/**
* 是否使用扬声器 
* bSpeaker true - 当前使用扬声器
**/ 
- (int)onOverrideSpeaker:(BOOL)bSpeaker;

/**
* 管理员发起屏幕共享或者取消共享请求
**/
- (int)onGrandScrshare:(BOOL)beGrant 
andopid:(u_int64_t)opid;

/**
* 拒绝屏幕共享请求
**/
- (int)onRejectScrshare:(NSArray *_Nullable)idArr;

/**
* 点名
* userid - 用户id
* nickName - 用户昵称
* countDown - 剩余时间(单位秒)
**/
- (int)onRollCall:(u_int64_t)userid
andFriendName:(NSString *_Nullable)nickName
andCountDown:(int)countDown;

/**
* 点名结束
**/
- (int)onRollCallEnd;

/**
* 获取音频信道
* rouType : 0 - 耳机; 1 - 蓝牙耳机; 2 - 扬声器; 3 - 手机听筒;
**/
- (void)onConfClientAVaudioSessionRouteChange:(int)routeType;

/**
* 视频旋转角度回调
* mOwnId - 用户id
* rotate - 角度
**/
- (void)onConfClientChangeRotate:(u_int64_t)mOwnId 
andRotate:(int)rotate;

/**
* 标记直播状态 - 
* makeShare: true - 断线重连后开启屏幕共享 ; false - 断线重连后开启屏幕共享;
**/
- (void)onUpDateMakeShared:(BOOL)makeShared;
```

## 4 <span id="standard">标准流程</span>

### 4.1 初始化
```
WHConfClient *confSdk = [[WHConfClient alloc] initWithDelegate:(id<WHConfClientDelegate>)clientDelegate];
```

### 4.2 连接服务器
```
[confSdk connect:userName password:pwd nickName:nickName serverIPS:serverIPS];

回调结果
- (int)onAuthenticated:(int)nResulte 
connType:(u_char)connType 
connIndex:(u_short)connIndex{
// 更新UI
}

```

### 4.3 获取会议室列表
```
[confSdk getRoomattrList];;
回调结果 
- (int)onGetRoomAttrSimpleList:(int)nResulte 
roomAttrs:(NSArray *_Nullable)arrRoomAttr{
//更新UI
}

```

### 4.4 进入会议室
```
[confSdk joinRoom:mJoinRoomID roomPwd:mRoomPassword];
回调接口
- (int)onJoinConfroom:(int)nResult 
roomID:(ROOMID_TYPE)roomID 
userID:(u_int64_t)userID 
nickName:(NSString *_Nullable)nickName{
// 更新UI
}
```

### 4.5 启动音视频模块
```
int audio = [confSdk startAudio];
int video = [confSdk startCamera:videoSize fps:fps isFront:bfront];;
```

### 4.6 观看用户视频
```
[confSdk queryVideo:userID videoIndex:ucIndex];
回调结果
- (int)onQueryvideo:(int)nResult 
operator:(u_int64_t)opID 
videoSessionID:(uint64_t)sessionID{
// 更新UI
}    
```



## 附表1 认证结果说明

|  详情| 描述 | 值 |
| ------ | ------ | ------ |
|  操作成功                                                              |  whErrSuccess                              | 0
|  操作失败                                                              |  whErrFailed                                  |  60000
|  未找到                                                                  |  whErrNotfind                                |  60042
|  不支持的                                                              |  whErrNotsupported                      |  60043
|  已经达到最大数量                                                |  whErrReachmaxsize                    |  60044
|  超出设定的范围                                                    |  whErrOutofrange                         |  60045
|  正忙，稍候再试                                                    |  whErrIsbusing                              |  60046
|  未处理的命令                                                        |  whErrUnhandledcmd                   |  60047
|  会议密码错误                                                        |  whErrRoompwderror                   |  60048
|  本账号另外地点登陆                                             |  whErrKickoutbyanother               |  60049
|  已经存在                                                               |  whErrAlreadyexists                      |  60050
|  找不到该会议室                                                    |  whErrRoomid                               |  60051
|  数据异常                                                               |  whErrDataexception                    |  60052
|  认证未回应                                                           |  whErrAuthnoresponse                  |  60053
|  被管理员请出会议室                                             |  whErrKickoutByAdmin                 |  60059
|  验证码无效                                                           |  whErrIdentCodeInvalid                |  60061
|  会议室已锁定                                                        |  whErrRoomlocked                       |  60064
|  等待用户离开                                                        |  whErrWaitingUserexit                   |  60065
|  拒绝                                                                      |  whErrReject                                  |  60066
|  同意                                                                      |  whErrAgree                                   |  60067
|  无权限                                                                   |  whErrNoRight                               |  60068
|  会议过期                                                               |  whErrExpire                                   |  60069
|  账号被禁用                                                            |  whErrAccountIsDisabled              |  60071
|  账号被删除                                                            |  whErrAccountHasDeleted            |  60072
|  会议处于删除状态                                                 |  whErrRoomHasBeenDeleted        |  60108
|  认证到期                                                                |  whErrSrvArExpire                         |  60109
| 找不到会议室                                                          |  whErrRoomNotFound                  |  60111
|  用户名为空                                                             |  whErrUserNameIsEmpty             |  61002
|  用户没有操作权限                                                  |  whErrUserNoOperPrivsEx           |  61015
|  用户没有分配视频窗口                                           |  whErrVideoNotView                     |  61018
|  摄像头未打开                                                         |  whErrCameraNotOpen                 |  64008
|  未知错误                                                                |  whErrUnknown                             |  65535

## 附表2 sTypePriv(用户权限)类别

|  详情| 值| 类型 |
| ------ | ------ | ------ |
|视频权限             |vquery      | NSString
|文字聊天权限      |chat          | NSString
|录制视频权限      |record       |NSString
|电子版本权限      |wbd          |NSString
|屏幕共享权限      |scr            |NSString
|媒体播放权限      |media       |NSString
|同步权限             |sync          |NSString


## 附表3 relayProtoId详情
|  详情| 描述 | 值 |
| ------ | ------ | ------ |
|获取摄像头属性                                | relayproto_GetVcapInfo                    |    65001
|设置摄像头属性                                | relayproto_SetVcapInfo                    |    65002
|获取麦克风属性                                | relayproto_GetAudioInfo                   |    65003
|设置麦克风属性                                | relayproto_SetAudioInfo                   |    65004
|服务器获取用户多媒体信息 请求      | relayproto_GetAVInfoReq                 |    65005
|用户向服务器发送多媒体信息 响应   |relayproto_GetAVInfoRsp                  |    65006
|用户向服务器发送文字信息               |relayproto_ChatmsgInfo                    |    65008
|用户被踢出会议室                             | relayproto_KickoutCmd                    |    65009
|获取影音播放媒体信                         | relayproto_Mediaplayerinfo               |    65011
|暂停影音播放                                    | relayproto_MediaPause                    |    65012
|继续影音播放                                    | relayproto_MediaContinue                |    65013    
|停止影音                                           | relayproto_MediaStop                       |    65014
|获取影音播放音量                             | relayproto_MediaVolume                  |    65016
|远程同步                                           | relayproto_GrantDataSync                |    65021
|远程上麦                                           | relayproto_GrantMakeASpeaker       |    65022
|远程共享                                           | relayproto_GrantScrsharer                |    65023
|远程影音                                           | relayproto_GrantMediaer                   |    65024
|管理员结束会议                                | relayproto_CloseConference              |    65029
|拒绝屏幕共享                                    | relayproto_RejectScrsharerReq         |    65041
|点名请求                                           | relayproto_RollCallReq                       |    65047
|点名响应                                           | relayproto_RollCallRsp                       |    65048

## 附表4 网络连接类型
|  详情| 描述| 值 |
| ------ | ------ | ------ |
|主连接          | conntype_Command                 |   0
|音频              | conntype_Audio                        |   1
|屏幕共享       | conntype_Scrshare                   |   3
|文件共享       | conntype_Fileshare                   |   4
|视频              | conntype_Video                        |   5



