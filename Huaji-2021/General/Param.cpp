#include "Param.h"
#include<yaml-cpp/yaml.h>
using namespace rm;
using namespace std;

Param::Param()
{
	YAML::Node config = YAML::LoadFile("../config.yml");
	//debug赋值
	debug_drawRoiRect = config["Armor"]["debug_drawRoiRect"].as<bool>();
	debug_showRoiImg = config["Armor"]["debug_showRoiImg"].as<bool>();
	debug_showImg = config["Armor"]["debug_showImg"].as<bool>();

	//基类参数赋值
	int i = 0;
	for (YAML::const_iterator it = config["Armor"]["roi_scale_size"].begin(); it != config["Armor"]["roi_scale_size"].end(); it++)
	{
		roi_scale_size[i] = it->as<int>();
		i++;
	}
}

Param::Param(const std::string& filename)
{
	YAML::Node config = YAML::LoadFile(filename);
	//debug赋值
	debug_drawRoiRect = config["Armor"]["debug_drawRoiRect"].as<bool>();
	debug_showRoiImg = config["Armor"]["debug_showRoiImg"].as<bool>();
	debug_showImg = config["Armor"]["debug_showImg"].as<bool>();

	//基类参数赋值
	int i = 0;
	for (YAML::const_iterator it = config["Armor"]["roi_scale_size"].begin(); it != config["Armor"]["roi_scale_size"].end(); it++)
	{
		roi_scale_size[i] = it->as<int>();
		i++;
	}

}



ArmorParam::ArmorParam()
{

}
