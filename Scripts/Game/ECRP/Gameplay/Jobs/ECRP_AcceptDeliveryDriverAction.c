// Native contextual action exposed by the Job Board's ActionsManagerComponent.
class ECRP_AcceptDeliveryDriverAction : ScriptedUserAction
{
	protected static const float MAXIMUM_DISTANCE = 3.0;

	override void PerformAction(IEntity pOwnerEntity, IEntity pUserEntity)
	{
		Print("ECRP: Delivery Driver job accepted.", LogLevel.NORMAL);
	}

	override bool CanBeShownScript(IEntity user)
	{
		return IsUserInRange(user);
	}

	override bool CanBePerformedScript(IEntity user)
	{
		return IsUserInRange(user);
	}

	override bool HasLocalEffectOnlyScript()
	{
		return true;
	}

	override bool GetActionNameScript(out string outName)
	{
		outName = "Accept Delivery Driver Job";
		return true;
	}

	protected bool IsUserInRange(IEntity user)
	{
		IEntity owner = GetOwner();

		if (!owner || !user)
			return false;

		return vector.Distance(owner.GetOrigin(), user.GetOrigin()) <= MAXIMUM_DISTANCE;
	}
}
