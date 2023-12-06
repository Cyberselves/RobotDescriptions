#ifdef NO_INCLUDE_DIR
#include "tmr_robot_state.h"
#include "tmr_print.h"
#else
#include "tmr/tmr_robot_state.h"
#include "tmr/tmr_print.h"
#endif

#include <memory>
#include <cstring>
#include <sstream>
#include <iostream>

#include <map>

namespace tmr
{

class DataTable
{
public:
	struct Item {
		void *dst;
		bool required;
		bool checked;
		enum { REQUIRED = 1 };
		Item() : dst(nullptr), required(false), checked(false) {};
		Item(void *d) : dst(d), required(false), checked(false) {};
		Item(void *d, bool r) : dst(d), required(r), checked(false) {};
	};
private:
	std::map<std::string, Item> _item_map;

public:
	DataTable(RobotState *rs)
	{
		tmr_DEBUG_STREAM("Create DataTable");

		_item_map.clear();
		//_item_map[""] = { Item:, &rs- };
		_item_map["Robot_Link"         ] = { &rs->_is_linked_, };
		_item_map["Robot_Error"        ] = { &rs->_has_error_, Item::REQUIRED };
		_item_map["Project_Run"        ] = { &rs->_is_proj_running_ };
		_item_map["Project_Pause"      ] = { &rs->_is_proj_paused_ };
		_item_map["Safeguard_A"        ] = { &rs->_is_safeguard_A_triggered_};
		_item_map["ESTOP"              ] = { &rs->_is_ESTOP_pressed_ };
		_item_map["Camera_Light"       ] = { &rs->_camera_light_ };
		_item_map["Error_Code"         ] = { &rs->_error_code_ };
		_item_map["Joint_Angle"        ] = { &rs->_joint_angle_, Item::REQUIRED };
		_item_map["Coord_Robot_Flange" ] = { &rs->_flange_pose_ };
		_item_map["Coord_Robot_Tool"   ] = { &rs->_tool_pose_, Item::REQUIRED };
		_item_map["TCP_Force"          ] = { &rs->_tcp_force_vec_ };
		_item_map["TCP_Force3D"        ] = { &rs->_tcp_force_ };
		_item_map["TCP_Speed"          ] = { &rs->_tcp_speed_vec_ };
		_item_map["TCP_Speed3D"        ] = { &rs->_tcp_speed_ };
		_item_map["Joint_Speed"        ] = { &rs->_joint_speed_ };
		_item_map["Joint_Torque"       ] = { &rs->_joint_torque_ };
		_item_map["Project_Speed"      ] = { &rs->_proj_speed_ };
		_item_map["MA_Mode"            ] = { &rs->_ma_mode_ };
		_item_map["Robot_Light"        ] = { &rs->_robot_light_ };
		_item_map["Ctrl_DO0"           ] = { &rs->_ctrller_DO_[ 0] };
		_item_map["Ctrl_DO1"           ] = { &rs->_ctrller_DO_[ 1] };
		_item_map["Ctrl_DO2"           ] = { &rs->_ctrller_DO_[ 2] };
		_item_map["Ctrl_DO3"           ] = { &rs->_ctrller_DO_[ 3] };
		_item_map["Ctrl_DO4"           ] = { &rs->_ctrller_DO_[ 4] };
		_item_map["Ctrl_DO5"           ] = { &rs->_ctrller_DO_[ 5] };
		_item_map["Ctrl_DO6"           ] = { &rs->_ctrller_DO_[ 6] };
		_item_map["Ctrl_DO7"           ] = { &rs->_ctrller_DO_[ 7] };
		_item_map["Ctrl_DO8"           ] = { &rs->_ctrller_DO_[ 8] };
		_item_map["Ctrl_DO9"           ] = { &rs->_ctrller_DO_[ 9] };
		_item_map["Ctrl_DO10"          ] = { &rs->_ctrller_DO_[10] };
		_item_map["Ctrl_DO11"          ] = { &rs->_ctrller_DO_[11] };
		_item_map["Ctrl_DO12"          ] = { &rs->_ctrller_DO_[12] };
		_item_map["Ctrl_DO13"          ] = { &rs->_ctrller_DO_[13] };
		_item_map["Ctrl_DO14"          ] = { &rs->_ctrller_DO_[14] };
		_item_map["Ctrl_DO15"          ] = { &rs->_ctrller_DO_[15] };
		_item_map["Ctrl_DI0"           ] = { &rs->_ctrller_DI_[ 0] };
		_item_map["Ctrl_DI1"           ] = { &rs->_ctrller_DI_[ 1] };
		_item_map["Ctrl_DI2"           ] = { &rs->_ctrller_DI_[ 2] };
		_item_map["Ctrl_DI3"           ] = { &rs->_ctrller_DI_[ 3] };
		_item_map["Ctrl_DI4"           ] = { &rs->_ctrller_DI_[ 4] };
		_item_map["Ctrl_DI5"           ] = { &rs->_ctrller_DI_[ 5] };
		_item_map["Ctrl_DI6"           ] = { &rs->_ctrller_DI_[ 6] };
		_item_map["Ctrl_DI7"           ] = { &rs->_ctrller_DI_[ 7] };
		_item_map["Ctrl_DI8"           ] = { &rs->_ctrller_DI_[ 8] };
		_item_map["Ctrl_DI9"           ] = { &rs->_ctrller_DI_[ 9] };
		_item_map["Ctrl_DI10"          ] = { &rs->_ctrller_DI_[10] };
		_item_map["Ctrl_DI11"          ] = { &rs->_ctrller_DI_[11] };
		_item_map["Ctrl_DI12"          ] = { &rs->_ctrller_DI_[12] };
		_item_map["Ctrl_DI13"          ] = { &rs->_ctrller_DI_[13] };
		_item_map["Ctrl_DI14"          ] = { &rs->_ctrller_DI_[14] };
		_item_map["Ctrl_DI15"          ] = { &rs->_ctrller_DI_[15] };
		_item_map["Ctrl_AO0"           ] = { &rs->_ctrller_AO_[ 0] };
		_item_map["Ctrl_AO1"           ] = { &rs->_ctrller_AO_[ 1] };
		_item_map["Ctrl_AI0"           ] = { &rs->_ctrller_AI_[ 0] };
		_item_map["Ctrl_AI1"           ] = { &rs->_ctrller_AI_[ 1] };
		_item_map["End_DO0"            ] = { &rs->_ee_DO_[0] };
		_item_map["End_DO1"            ] = { &rs->_ee_DO_[1] };
		_item_map["End_DO2"            ] = { &rs->_ee_DO_[2] };
		_item_map["End_DO3"            ] = { &rs->_ee_DO_[3] };
		_item_map["End_DI0"            ] = { &rs->_ee_DI_[0] };
		_item_map["End_DI1"            ] = { &rs->_ee_DI_[1] };
		_item_map["End_DI2"            ] = { &rs->_ee_DI_[2] };
		_item_map["End_DI3"            ] = { &rs->_ee_DI_[3] };
		_item_map["End_AO0"            ] = { &rs->_ee_AO_[0] };
		_item_map["End_AO1"            ] = { &rs->_ee_AO_[1] };
		_item_map["End_AI0"            ] = { &rs->_ee_AI_[0] };
		_item_map["End_AI1"            ] = { &rs->_ee_AI_[1] };
	}
	std::map<std::string, Item>  & get() { return _item_map; }
	std::map<std::string, Item>::iterator find(const std::string &name) { return _item_map.find(name); }
	std::map<std::string, Item>::iterator end() { return _item_map.end(); }
};

RobotState::RobotState()
{
	tmr_DEBUG_STREAM("tmr::RobotState::RobotState");

	_data_table = new DataTable(this);

	_joint_angle.assign(DOF, 0.0);
	_flange_pose.assign(6, 0.0);
	_tool_pose.assign(6, 0.0);
	_tcp_force_vec.assign(3, 0.0);
	_tcp_speed_vec.assign(6, 0.0);
	_joint_speed.assign(DOF, 0.0);
	_joint_torque.assign(DOF, 0.0);
	_tcp_frame.assign(6, 0.0);
	_tcp_cog.assign(6, 0.0);

	_ctrller_DO.assign(16, false);
	_ctrller_DI.assign(16, false);
	_ctrller_AO.assign(2, 0.0);
	_ctrller_AI.assign(2, 0.0);
	_ee_DO.assign(4, false);
	_ee_DI.assign(4, false);
	_ee_AO.assign(2, 0.0);
	_ee_AI.assign(2, 0.0);

	_f_deserialize_item[0] = std::bind(&RobotState::_deserialize_skip,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
	_f_deserialize_item[1] = std::bind(&RobotState::_deserialize_copy_wo_check,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	_f_deserialize = std::bind(&RobotState::_deserialize_first_time, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}
RobotState::~RobotState()
{
	tmr_DEBUG_STREAM("tmr::RobotState::~RobotState");
	delete _data_table;
}

void RobotState::set_joint_states(const std::vector<double> &pos, const std::vector<double> &vel, const std::vector<double> &tor)
{
	_joint_angle = pos;
	_joint_speed = vel;
	_joint_torque = tor;
}

std::vector<double> RobotState::mtx_flange_pose()
{
	std::vector<double> rv(_flange_pose.size());
	std::lock_guard<std::mutex> lck(mtx);
	rv = _flange_pose;
	return rv;
}
std::vector<double> RobotState::mtx_joint_angle()
{
	std::vector<double> rv(_joint_angle.size());
	std::lock_guard<std::mutex> lck(mtx);
	rv = _joint_angle;
	return rv;
}
std::vector<double> RobotState::mtx_tool_pose()
{
	std::vector<double> rv(_tool_pose.size());
	std::lock_guard<std::mutex> lck(mtx);
	rv = _tool_pose;
	return rv;
}
std::vector<double> RobotState::mtx_tcp_force_vec()
{
	std::vector<double> rv(_tcp_force_vec.size());
	std::lock_guard<std::mutex> lck(mtx);
	rv = _tcp_force_vec;
	return rv;
}
std::vector<double> RobotState::mtx_tcp_speed_vec()
{
	std::vector<double> rv(_tcp_speed_vec.size());
	std::lock_guard<std::mutex> lck(mtx);
	rv = _tcp_speed_vec;
	return rv;
}
std::vector<double> RobotState::mtx_joint_speed()
{
	std::vector<double> rv(_joint_speed.size());
	std::lock_guard<std::mutex> lck(mtx);
	rv = _joint_speed;
	return rv;
}
std::vector<double> RobotState::mtx_joint_torque()
{
	std::vector<double> rv(_joint_torque.size());
	std::lock_guard<std::mutex> lck(mtx);
	rv = _joint_torque;
	return rv;
}
std::string RobotState::mtx_error_content()
{
	std::string rv;
	std::lock_guard<std::mutex> lck(mtx);
	rv = _error_content;
	return rv;
}
std::vector<unsigned char> RobotState::mtx_ctrller_DO()
{
	std::vector<unsigned char> rv;
	std::lock_guard<std::mutex> lck(mtx);
	rv = _ctrller_DO;
	return rv;
}
std::vector<unsigned char> RobotState::mtx_ctrller_DI()
{
	std::vector<unsigned char> rv;
	std::lock_guard<std::mutex> lck(mtx);
	rv = _ctrller_DI;
	return rv;
}
std::vector<float> RobotState::mtx_ctrller_AO()
{
	std::vector<float> rv;
	std::lock_guard<std::mutex> lck(mtx);
	rv = _ctrller_AO;
	return rv;
}
std::vector<float> RobotState::mtx_ctrller_AI()
{
	std::vector<float> rv;
	std::lock_guard<std::mutex> lck(mtx);
	rv = _ctrller_AO;
	return rv;
}
std::vector<unsigned char> RobotState::mtx_ee_DO()
{
	std::vector<unsigned char> rv;
	std::lock_guard<std::mutex> lck(mtx);
	rv = _ee_DO;
	return rv;
}
std::vector<unsigned char> RobotState::mtx_ee_DI()
{
	std::vector<unsigned char> rv;
	std::lock_guard<std::mutex> lck(mtx);
	rv = _ee_DI;
	return rv;
}
std::vector<float> RobotState::mtx_ee_AI()
{
	std::vector<float> rv;
	std::lock_guard<std::mutex> lck(mtx);
	rv = _ee_AI;
	return rv;
}

size_t RobotState::_deserialize_get_name(std::string &name, const char *data, size_t offset)
{
	size_t boffset = offset;
	unsigned short uslen; // 2 bytes

	// item name length
	memcpy(&uslen, data + boffset, 2);
	boffset += 2;
	// item name
	name = std::string{data + boffset, uslen};
	boffset += uslen;
	// skip item
	memcpy(&uslen, data + boffset, 2);
	boffset += 2 + uslen;
	return boffset;
}
size_t RobotState::_deserialize_skip(void *dst, const char *data, size_t offset)
{
	size_t boffset = offset;
	unsigned short uslen; // 2 bytes

	// skip item name
	memcpy(&uslen, data + boffset, 2);
	boffset += 2 + uslen;
	// skip item
	memcpy(&uslen, data + boffset, 2);
	boffset += 2 + uslen;

	if (dst) {}
	return boffset;
}
size_t RobotState::_deserialize_copy_wo_check(void *dst, const char *data, size_t offset)
{
	size_t boffset = offset;
	//size_t bsize = 2;
	unsigned short uslen; // 2 bytes

	// skip item name
	memcpy(&uslen, data + boffset, 2);
	boffset += 2 + uslen;
	// item data length
	memcpy(&uslen, data + boffset, 2);
	boffset += 2;
	// item data
	//bsize = uslen;
	memcpy(dst, data + boffset, uslen);
	boffset += uslen;
	return boffset;
}

size_t RobotState::_deserialize_first_time(const char *data, size_t size, bool lock)
{
	size_t boffset = 0;
	size_t count = 0;
	size_t check_count = 0;
	size_t skip_count = 0;
	unsigned short uslen = 0; // 2 bytes
	std::string item_name;

	tmr_INFO_STREAM("TM Flow DataTable Checked Item: ");
	_item_updates.clear();
	//_f_deserialize_item.clear();

	while (boffset < size && count < 100) {
		//boffset = _deserialize_get_name(item_name, data, boffset);
		// item name length
		memcpy(&uslen, data + boffset, 2);
		boffset += 2;
		// item name
		item_name = std::string{data + boffset, uslen};
		boffset += uslen;

		ItemUpdate update{ nullptr, ItemUpdate::SKIP };
		//std::function<size_t (void *, const char *, size_t)> func;
		auto iter = _data_table->find(item_name);
		if (iter != _data_table->end()) {
			update.dst = iter->second.dst;
			update.func = ItemUpdate::UPDATE;
			//func = std::bind(&RobotState::_deserialize_copy_wo_check, iter->second.dst,
			//	std::placeholders::_2, std::placeholders::_3);
			iter->second.checked = true;
			tmr_INFO_STREAM("- " << item_name << " - checked");
			++check_count;
		}
		else {
			//func = std::bind(&RobotState::_deserialize_skip, nullptr,
			//	std::placeholders::_2, std::placeholders::_3);
			tmr_INFO_STREAM("- " << item_name << " - skipped");
			++skip_count;
		}
		_item_updates.push_back({ update.dst, update.func });
		//_f_deserialize_item.push_back(func);

		// item data length
		memcpy(&uslen, data + boffset, 2);
		boffset += 2;
		if (update.func == ItemUpdate::SKIP) {
			// skip item
			boffset += uslen;
		}
		else {
			// item data
			memcpy(update.dst, data + boffset, uslen);
			boffset += uslen;
		}
		++count;
	}
	tmr_INFO_STREAM("Total " << _item_updates.size() << " item," <<
		check_count << " checked, " << skip_count << " skipped");
	//tmr_INFO_STREAM("Checked " << _f_deserialize_item.size() << " item, " <<
	//	check_count << " checked, " << skip_count << " skipped");

	_deserialize_update(lock);

	for (auto iter : _data_table->get()) {
		if (iter.second.required && !iter.second.checked) {
			tmr_ERROR_STREAM("Required item" << iter.first << " is NOT checked");
		}
	}

	_f_deserialize = std::bind(&RobotState::_deserialize, this,
		std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

	return boffset;
}
size_t RobotState::_deserialize(const char *data, size_t size, bool lock)
{
	size_t boffset = 0;

	for (auto &update : _item_updates) {
		boffset = _f_deserialize_item[update.func](update.dst, data, boffset);
	}
	//for (auto &f : _f_deserialize_item) {
	//	boffset = f(data, boffset);
	//}

	/*
	// Robot_Link (2 + 10 + 2 + 1 = 15)
	boffset = _deserialize_copy_wo_check(&_is_linked_, data, boffset); // 15

	// Robot_Error (2 + 11 + 2 + 1 = 16)
	boffset = _deserialize_copy_wo_check(&_has_error_, data, boffset); // 31

	// Project_Edit

	// Project_Run (2 + 11 + 2 + 1 = 16)
	boffset = _deserialize_copy_wo_check(&_is_proj_running_, data, boffset); // 47
	
	// Project_Pause
	boffset = _deserialize_copy_wo_check(&_is_proj_paused_, data, boffset);

	// Safeguard_A
	boffset = _deserialize_copy_wo_check(&_is_safeguard_A_triggered_, data, boffset);

	// ESTOP
	boffset = _deserialize_copy_wo_check(&_is_ESTOP_pressed_, data, boffset);

	// Camera_Light
	boffset = _deserialize_copy_wo_check(&_camera_light_, data, boffset);

	// Robot_Model

	// Error_Code (2 + 10 + 2 + 4 = 18)
	boffset = _deserialize_copy_wo_check(&_error_code_, data, boffset);
	*/
	// Error_Content
	/*{
		std::unique_lock<std::mutex> lck(mtx, std::defer_lock);
		if (use_mtx) { lck.lock(); }

		size_t bsize = 2;
		unsigned short uslen;
		memcpy(&uslen, data + boffset, bsize);
		boffset += bsize + uslen; // = 13
		memcpy(&uslen, data + boffset, bsize);
		boffset += bsize;
		if (uslen > 0) {
			bsize = uslen;
			{
				std::stringstream ss;
				for (size_t i = 0; i < bsize; ++i) {
					ss << *(data + boffset + i);
				}
				_error_content = ss.str();
			}
			boffset += bsize;
		}
	}*/
	/*
	// Error_Time

	// Coord_Base_Flange
	//boffset = _deserialize_copy_wo_check(&_flange_pose_, data, boffset);

	// Joint_Angle
	boffset = _deserialize_copy_wo_check(&_joint_angle_, data, boffset);

	// Coord_Base_Tool
	//boffset = _deserialize_copy_wo_check(&_tool_pose_, data, boffset);

	// Coord_Robot_Flange
	boffset = _deserialize_copy_wo_check(&_flange_pose_, data, boffset);

	// Coord_Robot_Tool
	boffset = _deserialize_copy_wo_check(&_tool_pose_, data, boffset);

	// TCP_Force 12
	boffset = _deserialize_copy_wo_check(&_tcp_force_vec_, data, boffset);

	// TCP_Force3D 4
	boffset = _deserialize_copy_wo_check(&_tcp_force_, data, boffset);

	// TCP_Speed 24
	boffset = _deserialize_copy_wo_check(&_tcp_speed_vec_, data, boffset);

	// TCP_Speed3D 4
	boffset = _deserialize_copy_wo_check(&_tcp_speed_, data, boffset);

	// Joint_Speed 24
	boffset = _deserialize_copy_wo_check(&_joint_speed_, data, boffset);

	// Joint_Torque 24
	boffset = _deserialize_copy_wo_check(&_joint_torque_, data, boffset);

	// TCP_Name

	// TCP_Value
	//boffset = _deserialize_copy_wo_check(&_tcp_frame_, data, boffset);

	// TCP_Mass
	//boffset = _deserialize_copy_wo_check(&_tcp_mass_, data, boffset);

	// TCP_MCF
	//boffset = _deserialize_copy_wo_check(&_tcp_cog_, data, boffset);

	// Project_Name

	// Project_Speed 1
	boffset = _deserialize_copy_wo_check(&_proj_speed_, data, boffset);

	// MA_Mode 4
	boffset = _deserialize_copy_wo_check(&_ma_mode_, data, boffset);

	// Stick_PlayPause
	//boffset = _deserialize_copy_wo_check(&_stick_play_pause_, data, boffset);

	// End_FreeBot
	//boffset = _deserialize_copy_wo_check(&, data, boffset);

	// Robot_Light
	boffset = _deserialize_copy_wo_check(&_robot_light_, data, boffset);

	// Ctrl_DOx
	for (int i = 0; i < 8; ++i) {
		boffset = _deserialize_copy_wo_check(&_ctrller_DO_[i], data, boffset);
	}
	// Ctrl_DIx
	for (int i = 0; i < 8; ++i) {
		boffset = _deserialize_copy_wo_check(&_ctrller_DI_[i], data, boffset);
	}
	// Ctrl_AOx
	for (int i = 0; i < 1; ++i) {
		boffset = _deserialize_copy_wo_check(&_ctrller_AO_[i], data, boffset);
	}
	// Ctrl_AIx
	for (int i = 0; i < 2; ++i) {
		boffset = _deserialize_copy_wo_check(&_ctrller_AI_[i], data, boffset);
	}
	// End_DOx
	for (int i = 0; i < 4; ++i) {
		boffset = _deserialize_copy_wo_check(&_ee_DO_[i], data, boffset);
	}
	// End_DIx
	for (int i = 0; i < 3; ++i) {
		boffset = _deserialize_copy_wo_check(&_ee_DI_[i], data, boffset);
	}
	// End_AOx
	//for (int i = 0; i < 1; ++i) {
	//	boffset = _deserialize_copy_wo_check(&_ee_AO_[i], data, boffset);
	//}
	// End_AIx
	for (int i = 0; i < 1; ++i) {
		boffset = _deserialize_copy_wo_check(&_ee_AI_[i], data, boffset);
	}
	*/

	_deserialize_update(lock);

	if (boffset > size) {
	}
	return boffset;
}

void RobotState::_deserialize_update(bool lock){
	// ---------------
	// update together
	// ---------------

	//const char c0 = 0;

	_is_linked = _is_linked_;
	_has_error = _has_error_;
	_is_proj_running = _is_proj_running_;
	_is_proj_paused = _is_proj_paused_;

	_is_safeguard_A_triggered = _is_safeguard_A_triggered_;
	_is_ESTOP_pressed = _is_ESTOP_pressed_;
	_camera_light = _camera_light_;
	_error_code = _error_code_;

	_proj_speed = _proj_speed_;
	_ma_mode = _ma_mode_;
	//_stick_play_pause = _stick_play_pause_;

	_robot_light = _robot_light_;

	{
		std::unique_lock<std::mutex> lck(mtx, std::defer_lock);
		if (lock) { lck.lock(); }

		_joint_angle = rads(_joint_angle_, DOF);

		si_pose(_flange_pose, _flange_pose_, 6);

		si_pose(_tool_pose, _tool_pose_, 6);

		for (int i = 0; i < 3; ++i) { _tcp_force_vec[i] = double(_tcp_force_vec_[i]); }

		_tcp_force = double(_tcp_force_);

		si_pose(_tcp_speed_vec, _tcp_speed_vec_, 6);

		_joint_speed = rads(_joint_speed_, DOF);

		_joint_torque = meters(_joint_torque_, DOF);

		// IO

		for (int i = 0; i < 8; ++i) { _ctrller_DO[i] = _ctrller_DO_[i]; }
		for (int i = 0; i < 8; ++i) { _ctrller_DI[i] = _ctrller_DI_[i]; }
		for (int i = 0; i < 2; ++i) { _ctrller_AO[i] = _ctrller_AO_[i]; }
		for (int i = 0; i < 2; ++i) { _ctrller_AI[i] = _ctrller_AI_[i]; }
		for (int i = 0; i < 4; ++i) { _ee_DO[i] = _ee_DO_[i]; }
		for (int i = 0; i < 4; ++i) { _ee_DI[i] = _ee_DI_[i]; }
		for (int i = 0; i < 2; ++i) { _ee_AO[i] = _ee_AO_[i]; }
		for (int i = 0; i < 2; ++i) { _ee_AI[i] = _ee_AI_[i]; }
	}
}

void RobotState::print()
{
	std::lock_guard<std::mutex> lck(mtx);

	std::cout << "Robot_Link=" << (int)_is_linked << "\n";
	std::cout << "Robot_Error=" << (int)_has_error << "\n";
	std::cout << "Project_Run=" << (int)_is_proj_running << "\n";
	std::cout << "Project_Pause=" << (int)_is_proj_paused << "\n";
	std::cout << "Safetyguard_A=" << (int)_is_safeguard_A_triggered << "\n";
	std::cout << "ESTOP=" << (int)_is_ESTOP_pressed << "\n";

	std::cout << "Joint_Angle={";
	for (auto &val : _joint_angle) { std::cout << val << ", "; }
	std::cout << "}\n";

	std::cout << "Coord_Robot_Tool0={";
	for (auto &val : _flange_pose) { std::cout << val << ", "; }
	std::cout << "}\n";

	std::cout << "Coord_Robot_Tool={";
	for (auto &val : _tool_pose) { std::cout << val << ", "; }
	std::cout << "}\n";

	std::cout << "Error_Code=" << _error_code << "\n";
	std::cout << "Error_Content=" << _error_content << "\n";
}

}