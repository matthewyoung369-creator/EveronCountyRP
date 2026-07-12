[ComponentEditorProps(
	category: "Everon County RP/Interaction",
	description: "Makes an entity available to the ECRP interaction framework"
)]
class ECRP_InteractableComponentClass : ScriptComponentClass
{
}

class ECRP_InteractableComponent : ScriptComponent
{
	protected ref array<ref ECRP_InteractionAction> m_aInteractionActions = {};

	bool RegisterInteractionAction(ECRP_InteractionAction action)
	{
		if (!action)
			return false;

		string interactionId = action.GetInteractionId();

		if (interactionId.IsEmpty())
			return false;

		if (FindInteractionAction(interactionId))
			return false;

		m_aInteractionActions.Insert(action);
		return true;
	}

	bool UnregisterInteractionAction(string interactionId)
	{
		ECRP_InteractionAction action = FindInteractionAction(interactionId);

		if (!action)
			return false;

		m_aInteractionActions.RemoveItem(action);
		return true;
	}

	void GetInteractionActions(notnull array<ref ECRP_InteractionAction> actions)
	{
		actions.Clear();

		foreach (ECRP_InteractionAction action : m_aInteractionActions)
		{
			if (action)
				actions.Insert(action);
		}
	}

	ECRP_InteractionAction FindInteractionAction(string interactionId)
	{
		if (interactionId.IsEmpty())
			return null;

		foreach (ECRP_InteractionAction action : m_aInteractionActions)
		{
			if (action && action.GetInteractionId() == interactionId)
				return action;
		}

		return null;
	}
}