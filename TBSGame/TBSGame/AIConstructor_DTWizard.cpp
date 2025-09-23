#include "AIConstructor_DTWizard.h"


bool AIConstructor_DTWizard::Init() {

	method = AIConstructorBase::Method::DT;
	return true;
}


/*
DefineActions creates all the possible actions that the AI can perform
*/
void AIConstructor_DTWizard::DefineActions()
{




}


void AIConstructor_DTWizard::DefineConsiderations()
{


}


/*
* DefineOptions links the Options with Considerations and Actions
*/
void AIConstructor_DTWizard::DefineOptions()
{

}







// ** Helper Funcitons **
// these link to the AI Framework and should not be edited 


void AIConstructor_DTWizard::AddActionByName(std::string _actionName, std::function<ActionStatus(AIBrainBlackboardBase&)> _function)
{

	//Define an action, and init with the function which will be called when the action is selected
	AIAction* _action = new AIAction();
	_action->Init(_actionName, _function);
	actions.insert({ _actionName, _action });
}

void AIConstructor_DTWizard::AddConsiderationByName(std::string _actionName, std::function<bool(AIBrainBlackboardBase&)> _function)
{

	//Define an action, and init with the function which will be called when the action is selected
	AIConsideration* _consideration = new AIConsideration();
	_consideration->Init(_actionName, _function);
	considerations.insert({ _actionName, _consideration });
}

void AIConstructor_DTWizard::AddOptionByName(std::string _optionName, std::string _actionName, int _priority)
{
	// create an option for action
	AIOption* _option = new AIOption();
	_option->Init(_optionName, actions[_actionName], _priority);
	options.insert({ _optionName, _option });
}

void AIConstructor_DTWizard::AddOptionConsideration(std::string _optionName, std::string _considerationName)
{
	// create an option for action


	options[_optionName]->AddOptionConsideration(considerations[_considerationName]);
}

void AIConstructor_DTWizard::AddSubReasonerOptionByName(std::string _subReasonerName, int _priority)
{

	/// create the Action - a SubReasoner Actions
	AIActionSubReasoner* _subReasoner = new AIActionSubReasoner();

	_subReasoner->Init(_subReasonerName, nullptr);
	actions.insert({ _subReasonerName, _subReasoner });

	// create the option, and link to the Action
	AIOption* _option = new AIOption();
	_option->Init(_subReasonerName, actions[_subReasonerName]);
	options.insert({ _subReasonerName, _option });


}


void AIConstructor_DTWizard::AddOptionsToSubReasoner(std::string _subreasoner, std::string _options)
{

	subReasonerLinks.insert({ _subreasoner, _options });



}

std::vector<std::string> AIConstructor_DTWizard::GetOptionNamesForKey(std::string _subreasoner)
{

	std::vector<std::string> _matches;
	for (std::multimap<std::string, std::string>::iterator it = subReasonerLinks.begin(); it != subReasonerLinks.end(); ++it) {

		if (it->first == _subreasoner)
		{
			_matches.push_back(it->second);
		}
	}

	return _matches;

}

